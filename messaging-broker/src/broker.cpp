#include "messaging-broker/broker.h"

#include <iostream>

using lzr::msg::Broker;

/**
 * Callback triggered when the connection is performed.
 *
 * @param p_mosq
 * @param p_obj
 * @param p_code
 */
void on_connect(struct mosquitto *p_mosq, void *p_obj, int p_code)
{
    // Early exit
    if (!p_obj)
    {
        return;
    }

    if (p_code == 0)
    {
        auto handler = static_cast<Broker *>(p_obj);
        handler->set_connection_accepted();
        return;
    }

    mosquitto_disconnect(p_mosq);
}

/**
 * Callback triggered when a message is received.
 *
 * @param p_mosq
 * @param p_obj
 * @param p_message
 * @param p_props
 */
void on_message(struct mosquitto *p_mosq, void *p_obj,
                const struct mosquitto_message *p_message,
                const mosquitto_property *p_props)
{
    (void)p_mosq;
    (void)p_props;

    if (!p_obj)
        return;

    auto handler = static_cast<Broker *>(p_obj);
    std::string payload{static_cast<char *>(p_message->payload),
                        static_cast<char *>(p_message->payload) +
                            p_message->payloadlen};
    handler->set_message_received(p_message->topic, payload);
}

Broker::Broker(std::string const &p_client_id, std::string const &p_host,
               unsigned const p_port)
    : m_client_id{p_client_id}
    , m_host{p_host}
    , m_port{p_port}
{
    m_handler = mosquitto_new(p_client_id.c_str(), false, this);

    if (!m_handler)
    {
        std::cout << "Error while creating broker for client " << p_client_id
                  << "." << std::endl;
        throw std::logic_error{"Error while creating broker\n"};
    }

    mosquitto_connect_callback_set(m_handler, on_connect);
    mosquitto_message_v5_callback_set(m_handler, on_message);
}

bool Broker::connect()
{
    auto result = mosquitto_connect_bind_v5(
        m_handler, m_host.c_str(), m_port, m_timeout.count(), nullptr, nullptr);

    if (result != MOSQ_ERR_SUCCESS)
    {
        std::cout << "Error: mosquitto_connect_bind_v5 failed." << std::endl;
        return false;
    }

    if (mosquitto_loop_start(m_handler) != MOSQ_ERR_SUCCESS)
    {
        mosquitto_reinitialise(m_handler, m_client_id.c_str(), false, this);
        mosquitto_connect_callback_set(m_handler, on_connect);
        mosquitto_message_v5_callback_set(m_handler, on_message);

        std::cout << "Error initialising MQTT connection with credentials."
                  << std::endl;
        return false;
    }

    // Wait until the connection is established
    std::unique_lock<std::mutex> lock(m_connected_mutex);
    auto connected = m_connection_accepted.wait_for(
        lock, m_timeout, [this] { return m_connected.load(); });

    return connected;
}

bool Broker::disconnect()
{
    if (!m_connected)
    {
        std::cout << "Broker already disconnected." << std::endl;
        return true;
    }

    if (mosquitto_loop_stop(m_handler, true) != MOSQ_ERR_SUCCESS)
    {
        std::cout << "Couldn't disconnect from server." << std::endl;
        return false;
    }

    if (mosquitto_disconnect(m_handler) != MOSQ_ERR_SUCCESS)
    {
        std::cout << "Couldn't disconnect from server." << std::endl;
        return false;
    }

    std::cout << "Broker successfully disconnected." << std::endl;
    m_connected = false;

    return true;
}

bool Broker::subscribe(std::string const &p_topic)
{
    if (!m_connected)
    {
        return false;
    }

    return (mosquitto_subscribe_v5(m_handler, nullptr, p_topic.c_str(), 0, 0,
                                   nullptr) == MOSQ_ERR_SUCCESS);
}

bool Broker::unsubscribe(std::string const &p_topic)
{
    return (mosquitto_unsubscribe_v5(m_handler, nullptr, p_topic.c_str(),
                                     nullptr) == MOSQ_ERR_SUCCESS);
}

void Broker::add_receiver(std::string const &p_callback,
                          std::shared_ptr<IMsgReceiver> p_receiver)
{
    std::lock_guard<std::mutex> lock{m_receivers_mutex};

    // Can't register twice the same callback
    if (m_receivers.find(p_callback) != m_receivers.cend())
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
    if (!m_connected)
    {
        std::cout
            << "Couldn't publish message since connection is not established."
            << std::endl;
        return false;
    }

    auto const result = mosquitto_publish_v5(
        m_handler, nullptr, p_topic.c_str(), p_message.size(),
        p_message.c_str(), 0, false, nullptr);

    return (result == MOSQ_ERR_SUCCESS);
}

void Broker::set_connection_accepted()
{
    m_connected = true;
    m_connection_accepted.notify_one();
}

void Broker::set_message_received(std::string const &p_topic,
                                  std::string const &p_message)
{
    // Iterate over list of receivers to notify about received message
    for (auto const &receiver : m_receivers)
    {
        receiver.second->on_receive(p_topic, p_message);
    }
}
