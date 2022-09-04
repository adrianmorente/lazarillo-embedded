#include "messaging-broker/pubsub/pubsub_factory.h"

namespace lzr
{
namespace msg
{
std::shared_ptr<MsgPublisher>
    createMsgPublisher(std::shared_ptr<IPubSubPublisher> p_publisher,
                       std::shared_ptr<serialization::SerializationFactory>
                           p_serialization_factory,
                       std::string const &p_name)
{
    return std::make_shared<MsgPublisher>(p_publisher, p_serialization_factory,
                                          p_name);
}

std::shared_ptr<MsgSubscriber> createMsgSubscriber(
    std::shared_ptr<IPubSubSubscriber> p_subscriber,
    std::shared_ptr<serialization::SerializationFactory>
        p_serialization_factory,
    std::shared_ptr<messages::MessageFactory> p_message_factory)
{
    return std::make_shared<MsgSubscriber>(p_subscriber, p_message_factory,
                                           p_serialization_factory);
}
} // namespace msg
} // namespace lzr