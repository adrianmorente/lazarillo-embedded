#include "messaging-broker/broker.h"

#include <algorithm>
#include <iostream>
#include <iterator>

using lzr::msg::Broker;

using namespace std::literals::chrono_literals;

constexpr struct timeval TIMEOUT_CMD = {0, 5000L};
constexpr auto TIMEOUT_PING{5000ms};
constexpr auto TIMEOUT_TRY_CONNECTION{100ms};

bool cmdRedis(redisContext *const p_context, std::string const &p_command,
              std::mutex &p_mutex)
{
    bool result{false};
    std::lock_guard<std::mutex> lock{p_mutex};

    auto reply = redisCommand(p_context, p_command.c_str());

    // redisCommand returns NULL when there's an error
    if (reply != nullptr)
    {
        freeReplyObject(reply);
        result = true;
    }

    return result;
}

Broker::Broker()
{
    m_thread_ping    = std::thread([this]() { thread_keep_alive(); });
    m_thread_connect = std::thread([this]() { thread_connect(); });
    m_thread_receive = std::thread([this]() { thread_watch_messages(); });
}

Broker::~Broker()
{
    m_running = false;
    m_cv_running.notify_all();

    auto join_thread = [](std::thread &thread)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    };

    join_thread(m_thread_ping);
    join_thread(m_thread_connect);
    join_thread(m_thread_receive);
}

std::shared_future<bool>
    Broker::connect_async(std::chrono::milliseconds const p_timeout)
{
    if (m_promise_connection_performed == nullptr)
    {
        // Check timeout to keep trying or not
        m_try_to_connect_no_timeout = (p_timeout == 0s);
        m_timeout_trying_connection = p_timeout;

        auto promise                   = std::make_unique<std::promise<bool>>();
        m_future_connection_performed  = promise->get_future().share();
        m_promise_connection_performed = std::move(promise);
    }

    return m_future_connection_performed;
}

std::shared_future<bool> Broker::disconnect_async()
{
    set_status(RedisStatus::DISCONNECTING);

    m_promise_connection_performed = nullptr;

    set_status(RedisStatus::NONE);

    auto promise           = std::make_unique<std::promise<bool>>();
    auto future_disconnect = promise->get_future().share();
    promise->set_value(true);
    return future_disconnect;
}

bool Broker::subscribe(std::string const &p_topic)
{
    std::lock_guard<std::mutex> lock{m_receivers_mutex};
    bool result{false};

    if (is_connected() && !topic_exists(p_topic))
    {
        std::string const command = "SUBSCRIBE " + p_topic;
        result = cmdRedis(m_sub_handler.get(), command, m_sub_mutex);

        if (result)
        {
            m_topics.emplace_back(p_topic);
        }
    }

    return result;
}

bool Broker::unsubscribe(std::string const &p_topic)
{
    std::lock_guard<std::mutex> lock{m_receivers_mutex};
    bool result{false};

    if (is_connected() && topic_exists(p_topic))
    {
        std::string const command = "UNSUBSCRIBE " + p_topic;
        result = cmdRedis(m_sub_handler.get(), command, m_sub_mutex);

        if (result)
        {
            m_topics.erase(
                std::find(m_topics.begin(), m_topics.end(), p_topic));
        }
    }

    return result;
}

void Broker::add_receiver(std::string const &p_callback,
                          std::shared_ptr<RedisReceiver> p_receiver)
{
    std::lock_guard<std::mutex> lock{m_receivers_mutex};

    // Can't register twice the same callback
    if (m_receivers.find(p_callback) == m_receivers.cend())
    {
        return;
    }

    m_receivers.insert({p_callback, std::move(p_receiver)});
}

void Broker::remove_receiver(std::string const &p_callback)
{
    std::lock_guard<std::mutex> lock{m_receivers_mutex};

    // Do nothing if callback is not even registered
    if (m_receivers.find(p_callback) == m_receivers.cend())
    {
        return;
    }

    m_receivers.erase(p_callback);
}

bool Broker::publish(std::string const &p_topic, std::string const &p_message)
{
    bool result{false};

    if (m_pub_handler && is_connected())
    {
        std::lock_guard<std::mutex> lock{m_pub_mutex};

        std::string const command{"PUBLISH " + p_topic + " " + p_message};
        result = cmdRedis(m_pub_handler.get(), command, m_pub_mutex);
    }

    return result;
}

void Broker::thread_keep_alive()
{
    while (m_running)
    {
        if (m_pub_handler && is_connected())
        {
            cmdRedis(m_pub_handler.get(), "PING", m_pub_mutex);

            if (m_pub_handler->err != 0)
            {
                set_status(RedisStatus::ERROR);
                connect_async();
            }
        }

        wait_with_condition(TIMEOUT_PING);
    }
}

void Broker::thread_connect()
{
    while (m_running)
    {
        if (m_try_to_connect_no_timeout)
        {
            perform_connection();
        }
        else
        {
            std::chrono::milliseconds time_to_retry{
                m_timeout_trying_connection};
            if (time_to_retry > 0ms)
            {
                time_to_retry -= TIMEOUT_TRY_CONNECTION;
                m_timeout_trying_connection = time_to_retry;
                perform_connection();
            }
            else
            {
                m_promise_connection_performed = nullptr;
            }
        }

        wait_with_condition(TIMEOUT_TRY_CONNECTION);
    }
}

void Broker::thread_watch_messages()
{
    while (m_running)
    {
        std::this_thread::sleep_for(10ms);

        if (m_sub_handler != nullptr && is_connected())
        {
            read_from_redis();
        }
        else
        {
            wait_with_condition(1000ms);
        }
    }
}

bool Broker::topic_exists(std::string const &p_topic) const
{
    auto const topic_it =
        std::find(m_topics.cbegin(), m_topics.cend(), p_topic);
    return (topic_it != m_topics.cend());
}

bool Broker::is_connected() const
{
    return (m_status == RedisStatus::CONNECTED);
}

void Broker::wait_with_condition(std::chrono::milliseconds p_timeout)
{
    std::unique_lock<std::mutex> lock(m_cv_running_mutex);
    m_cv_running.wait_for(lock, p_timeout);
}

void Broker::perform_connection()
{
    if (m_status == RedisStatus::CONNECTING ||
        m_status == RedisStatus::CONNECTED)
    {
        return;
    }

    // Change status to CONNECTING during performance of connection
    set_status(RedisStatus::CONNECTING, "Starting performance of connection.");

    // Lambda function for both pub and sub contexts
    auto handle_context = [this](redisContext &p_context, std::mutex &p_mutex)
    {
        // First condition group: try connection
        if (p_context == nullptr)
        {
            std::lock_guard<std::mutex> lock{p_mutex};
            p_context = redisContext{
                redisConnectWithTimeout(m_host.c_str(), m_port, TIMEOUT_CMD)};
        }
        else
        {
            std::lock_guard<std::mutex> lock{p_mutex};
            redisReconnect(p_context.get());
        }

        // Second condition group: connection failed
        if (p_context == nullptr || p_context->err)
        {
            std::string const msg{"Error: connection to Redis failed."};
            set_status(RedisStatus::ERROR, msg);
            std::cout << msg << std::endl;
        }
    };

    handle_context(m_pub_handler, m_pub_mutex);
    handle_context(m_sub_handler, m_sub_mutex);

    // Subscription to topics
    {
        std::lock_guard<std::mutex> lock{m_topics_mutex};
        for (auto const &topic : m_topics)
        {
            std::string const command = "SUBSCRIBE " + topic;
            cmdRedis(m_sub_handler.get(), command, m_sub_mutex);
        }
    }

    set_status(RedisStatus::CONNECTED, "Finish performance of connection.");

    if (m_promise_connection_performed != nullptr)
    {
        m_promise_connection_performed->set_value(true);
        m_promise_connection_performed = nullptr;
    }
}

void Broker::set_status(RedisStatus const p_status,
                        std::string const &p_description)
{
    std::lock_guard<std::mutex> lock{m_status_mutex};
    auto previous = m_status;
    m_status      = p_status;

    std::cout << "Changed Redis status from " << status_as_string(previous)
              << " to " << status_as_string(m_status)
              << ". Description: " << p_description << std::endl;

    // If it wasn't connected but it is now, notify
    if (previous != RedisStatus::CONNECTED &&
        m_status == RedisStatus::CONNECTED)
    {
        m_cv_running.notify_all();
    }
}

std::string Broker::status_as_string(RedisStatus const p_status)
{
    std::string status{""};

    switch (p_status)
    {
    case RedisStatus::NONE: status = "NONE"; break;
    case RedisStatus::CONNECTING: status = "CONNECTING"; break;
    case RedisStatus::CONNECTED: status = "CONNECTED"; break;
    case RedisStatus::DISCONNECTING: status = "DISCONNECTING"; break;
    case RedisStatus::ERROR: status = "ERROR"; break;
    }

    return status;
}

void Broker::read_from_redis()
{
    redisReply *redis_reply = nullptr;
    int reply_int{REDIS_ERR};

    {
        std::lock_guard<std::mutex> lock{m_sub_mutex};
        redisSetTimeout(m_sub_handler.get(), TIMEOUT_CMD);
        reply_int = redisGetReply(m_sub_handler.get(),
                                  reinterpret_cast<void **>(&redis_reply));
    }

    // Redis subscribed-to messages contains the topic on one index and the
    // message on another
    constexpr auto TOPIC_INDEX{1U};
    constexpr auto MESSAGE_INDEX{2U};

    switch (reply_int)
    {
    case REDIS_ERR: break;
    case REDIS_OK:
        auto const &topic           = redis_reply->element[TOPIC_INDEX];
        std::string const topic_str = std::string{topic->str, topic->len};

        auto const &message           = redis_reply->element[MESSAGE_INDEX];
        std::string const message_str = std::string{message->str, message->len};

        loop_on_receive(topic_str, message_str);
        break;
    }
}

void Broker::loop_on_receive(std::string const &p_topic,
                             std::string const &p_message) const
{
    std::lock_guard<std::mutex> lock{m_receivers_mutex};

    for (auto const &receiver : m_receivers)
    {
        receiver.second->on_receive(p_topic, p_message);
    }
}
