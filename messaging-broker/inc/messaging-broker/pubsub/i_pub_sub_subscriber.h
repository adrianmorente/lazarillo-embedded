#ifndef MESSAGING_BROKER_INC_PUBSUB_I_PUB_SUB_SUBSCRIBER_H
#define MESSAGING_BROKER_INC_PUBSUB_I_PUB_SUB_SUBSCRIBER_H

#include "messaging-broker/redis_receiver.h"

#include <string>
#include <vector>

namespace lzr
{
namespace msg
{
class IPubSubSubscriber
{
public:
    virtual ~IPubSubSubscriber() {}

    /**
     * Subscribe to a topic
     *
     * @param p_topic
     */
    virtual bool subscribe(std::string const &p_topic) = 0;

    /**
     * Unsubscribe from a topic
     *
     * @param p_topic
     */
    virtual bool unsubscribe(std::string const &p_topic) = 0;

    /**
     * Get the subscribed topics object
     *
     * @return std::vector<std::string>
     */
    virtual std::vector<std::string> get_subscribed_topics() = 0;

    /**
     * Sets an object as receiver of the given callback.
     *
     * @param p_message_name
     * @param p_receiver
     * @param p_callback_id
     */
    virtual void add_receiver(std::string const &p_message_name,
                              std::shared_ptr<RedisReceiver> p_receiver) = 0;

    /**
     * Removes the object set as callback receiver.
     *
     * @param p_callback_id
     */
    virtual void remove_receiver(std::string const &p_callback_id) = 0;

    /**
     * Checks if a callback has been registered for the given message
     *
     * @param p_callback_id
     * @return true
     * @return false
     */
    virtual bool has_receiver(std::string const &p_callback_id) const = 0;
};
} // namespace msg
} // namespace lzr

#endif // MESSAGING_BROKER_INC_PUBSUB_I_PUB_SUB_SUBSCRIBER_H
