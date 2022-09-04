#ifndef MESSAGING_BROKER_INC_MSG_PUBLISHER_H
#define MESSAGING_BROKER_INC_MSG_PUBLISHER_H

#include "i_pub_sub_publisher.h"
#include "messaging-broker/serialization/serialization_factory.h"

#include "messages-definition/i_base_message.h"

#include <string>

namespace lzr
{
namespace msg
{
class MsgPublisher
{
public:
    ~MsgPublisher() {}

    explicit MsgPublisher(std::shared_ptr<IPubSubPublisher> p_publisher,
                          std::shared_ptr<serialization::SerializationFactory>
                              p_serialization_factory,
                          std::string const &p_name);

    /**
     * Publishes a message in a topic.
     *
     * @param p_topic topic where the message will be published
     * @param p_message message that will be published
     * @return bool true if succesfully published, false otherwise
     */
    bool publish(std::string const &p_topic,
                 messages::IBaseMessage const &p_message);

private:
    std::shared_ptr<IPubSubPublisher> m_publisher;
    std::shared_ptr<serialization::SerializationFactory>
        m_serialization_factory;
    std::string m_name;
};
} // namespace msg
} // namespace lzr

#endif // MESSAGING_BROKER_INC_MSG_PUBLISHER_H
