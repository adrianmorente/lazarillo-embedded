#ifndef MESSAGING_BROKER_INC_BROKER_H
#define MESSAGING_BROKER_INC_BROKER_H

#include "i_msg_receiver.h"

#include <atomic>
#include <condition_variable>
#include <map>
#include <memory>
#include <mosquitto.h>
#include <mutex>
#include <string>
#include <vector>

namespace lzr
{
namespace msg
{
class Broker
{
public:
    Broker(std::string const &p_client_id, std::string const &p_host,
           unsigned const p_port);

    bool connect();

    bool disconnect();

    bool subscribe(std::string const &p_topic);

    bool unsubscribe(std::string const &p_topic);

    void add_receiver(std::string const &p_callback,
                      std::shared_ptr<IMsgReceiver> p_receiver);

    void remove_receiver(std::string const &p_callback);

    bool publish(std::string const &p_topic, std::string const &p_message);

    void set_connection_accepted();

    void set_message_received(std::string const &p_topic,
                              std::string const &p_message);

private:
    // Address of the server to connect to
    std::string m_host{"localhost"};

    // Port used for connecting to the server
    unsigned m_port{6379U};

    // Timeout used while connecting to MQTT server
    std::chrono::milliseconds m_timeout{10000U};

    // Client credentials used for connecting to server
    std::string m_client_id{""};

    // Holds internally if connection is established
    std::atomic_bool m_connected{false};
    std::condition_variable m_connection_accepted;
    mutable std::mutex m_connected_mutex;

    // List of receivers subscribed to message
    std::map<std::string, std::shared_ptr<IMsgReceiver>> m_receivers;
    mutable std::mutex m_receivers_mutex;

    // List of topics that broker is subscribed to
    std::vector<std::string> m_topics;
    mutable std::mutex m_topics_mutex;

    // Internal mosquitto handler
    mosquitto *m_handler;
};
} // namespace msg
} // namespace lzr

#endif // MESSAGING_BROKER_INC_BROKER_H
