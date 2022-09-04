#ifndef MESSAGING_BROKER_INC_BROKER_H
#define MESSAGING_BROKER_INC_BROKER_H

#include <atomic>
#include <condition_variable>
#include <future>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "broker_helper.h"
#include "messaging-broker/pubsub/i_pub_sub_publisher.h"
#include "messaging-broker/pubsub/i_pub_sub_subscriber.h"
#include "redis_receiver.h"

#include "messages-definition/i_base_message.h"

using namespace std::chrono_literals;

namespace lzr
{
namespace msg
{
using helper::redisContext; //< Helper context instead of actual Redis context

class Broker
    : public IPubSubPublisher
    , public IPubSubSubscriber
{
public:
    enum class RedisStatus : uint8_t
    {
        NONE = 0U,
        CONNECTING,
        CONNECTED,
        DISCONNECTING,
        ERROR
    };

    Broker();

    ~Broker();

    /**
     * Connection method. It will try connecting as many times as needed until
     * the timeout is exceeded.
     *
     * @param p_timeout if no timeout, keep trying
     * @return std::shared_future<bool> emitted as true when connected
     */
    std::shared_future<bool>
        connect_async(std::chrono::milliseconds const p_timeout = 0s);

    /**
     * Disconnect from the broker.
     *
     * @return std::shared_future<bool>
     */
    std::shared_future<bool> disconnect_async();

    /**
     * @copydoc IPubSubSubscriber::subscribe
     */
    bool subscribe(std::string const &p_topic) override;

    /**
     * @copydoc IPubSubSubscriber::unsubscribe
     */
    bool unsubscribe(std::string const &p_topic) override;

    /**
     * @copydoc IPubSubSubscriber::get_subscribed_topics
     */
    std::vector<std::string> get_subscribed_topics() override;

    /**
     * @copydoc IPubSubSubscriber::add_receiver
     */
    void add_receiver(std::string const &p_callback,
                      std::shared_ptr<RedisReceiver> p_receiver) override;

    /**
     * @copydoc IPubSubSubscriber::remove_receiver
     */
    void remove_receiver(std::string const &p_callback) override;

    /**
     * @copydoc IPubSubSubscriber::has_receiver
     */
    bool has_receiver(std::string const &p_callback_id) const override;

    /**
     * @copydoc IPubSubPublisher::publish
     */
    bool publish(std::string const &p_topic,
                 std::string const &p_message) override;

private:
    /**
     * Method executed in separate thread consistint in pinging the server to
     * keep alive the connection.
     */
    void thread_keep_alive();

    /**
     * Method executed in separate thread to perform the connection to the Redis
     * server.
     */
    void thread_connect();

    /**
     * Method executed in separate thread in order to parse the received
     * messages on loop.
     */
    void thread_watch_messages();

    /**
     * Checks internally if the specified topic has been subscribed to
     *
     * @param p_topic
     * @return true
     * @return false
     */
    bool topic_exists(std::string const &p_topic) const;

    /**
     * Checks internally if the client is connected to Redis server
     *
     * @return true
     * @return false
     */
    bool is_connected() const;

    /**
     * Uses mutex for waiting until a condition is satisfied.
     *
     * @param p_timeout
     */
    void wait_with_condition(std::chrono::milliseconds p_timeout);

    /**
     * Actually tries to connect to the redis server synchronously.
     */
    void perform_connection();

    /**
     * Set the status object
     *
     * @param p_status
     * @param p_description
     */
    void set_status(RedisStatus const p_status,
                    std::string const &p_description = "None");

    /**
     * Converts the RedisStatus value to string for printing
     *
     * @param p_status
     * @return std::string
     */
    std::string status_as_string(RedisStatus const p_status);

    /**
     * Method for looping indefinitely reading messages from buffer.
     */
    void read_from_redis();

    /**
     * Iterates over the list of receivers to notify them about the requested
     * topic.
     *
     * @param p_topic
     * @param p_message
     */
    void loop_on_receive(std::string const &p_topic,
                         std::string const &p_message) const;

    // Address of the server to connect to
    std::string const m_host{"localhost"};

    // Port used for connecting to the server
    unsigned const m_port{6379U};

    std::atomic<bool> m_running{false};
    std::atomic<bool> m_try_to_connect{false};
    std::atomic<bool> m_try_to_connect_no_timeout{false};

    // Timeout used while connecting to MQTT server
    std::chrono::milliseconds const m_timeout{10000U};
    std::chrono::milliseconds m_timeout_trying_connection;

    // Holds internally if connection is established
    RedisStatus m_status{RedisStatus::NONE};
    std::mutex m_status_mutex;

    // List of receivers subscribed to message
    std::unordered_map<std::string, std::shared_ptr<RedisReceiver>> m_receivers;
    mutable std::mutex m_receivers_mutex;

    // List of topics that broker is subscribed to
    std::vector<std::string> m_topics;
    mutable std::mutex m_topics_mutex;

    // Internal redis handlers (split for Pub and Sub)
    redisContext m_pub_handler;
    std::mutex m_pub_mutex;
    redisContext m_sub_handler;
    std::mutex m_sub_mutex;

    // Thread for "pinging" connection
    std::thread m_thread_ping;

    // Thread for initialising connection
    std::thread m_thread_connect;

    // Thread for receiving messages
    std::thread m_thread_receive;

    // Condition variable for joining the threads
    std::condition_variable m_cv_running;
    std::mutex m_cv_running_mutex;

    // Promise and future for handling performance of connection
    std::unique_ptr<std::promise<bool>> m_promise_connection_performed;
    std::shared_future<bool> m_future_connection_performed;
};
} // namespace msg
} // namespace lzr

#endif // MESSAGING_BROKER_INC_BROKER_H
