#ifndef MESSAGING_BROKER_INC_MESSAGING_BROKER_PUBSUB_I_PUB_SUB_PUBLISHER_H
#define MESSAGING_BROKER_INC_MESSAGING_BROKER_PUBSUB_I_PUB_SUB_PUBLISHER_H

#include <memory>
#include <string>

namespace lzr
{
namespace msg
{
class IPubSubPublisher
{
public:
    virtual ~IPubSubPublisher() {}

    /**
     * Published a message as string in a topic
     *
     * @param p_topic topic where to publish the message
     * @param p_message message as string to be published
     * @return bool true if successful, false otherwise
     */
    virtual bool publish(std::string const &p_topic,
                         std::string const &p_message) = 0;
};
} // namespace msg
} // namespace lzr

#endif // MESSAGING_BROKER_INC_MESSAGING_BROKER_PUBSUB_I_PUB_SUB_PUBLISHER_H
