#include "messaging-broker/redis_receiver.h"

using lzr::msg::RedisReceiver;

RedisReceiver::RedisReceiver() {}

void RedisReceiver::on_receive(std::string const &p_topic,
                               std::string const &p_message)
{
    if (m_dispatcher)
    {
        m_dispatcher->onRawData(p_topic, p_message);
    }
}
