#ifndef MESSAGING_BROKER_INC_MESSAGING_BROKER_I_REDIS_RECEIVER_H
#define MESSAGING_BROKER_INC_MESSAGING_BROKER_I_REDIS_RECEIVER_H

#include "redis_dispatcher.h"

#include <memory>
#include <string>

namespace lzr
{
namespace msg
{
class RedisReceiver
{
public:
    RedisReceiver();

    /**
     * Callback triggered when a message is received (as string) and then is
     * deserialized.
     *
     * @param p_topic
     * @param p_message
     */
    void on_receive(std::string const &p_topic, std::string const &p_message);

private:
    std::unique_ptr<RedisDispatcher> m_dispatcher;
};
} // namespace msg
} // namespace lzr

#endif // MESSAGING_BROKER_INC_MESSAGING_BROKER_I_REDIS_RECEIVER_H
