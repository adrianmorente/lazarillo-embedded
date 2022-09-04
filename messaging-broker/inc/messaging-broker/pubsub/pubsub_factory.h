#ifndef MESSAGING_BROKER_INC_PUBSUB_FACTORY_H
#define MESSAGING_BROKER_INC_PUBSUB_FACTORY_H

#include "i_pub_sub_publisher.h"
#include "i_pub_sub_subscriber.h"
#include "messaging-broker/serialization/serialization_factory.h"
#include "msg_publisher.h"
#include "msg_subscriber.h"

#include <memory>

namespace lzr
{
namespace msg
{
std::shared_ptr<MsgPublisher>
    createMsgPublisher(std::shared_ptr<IPubSubPublisher> p_publisher,
                       std::shared_ptr<serialization::SerializationFactory>
                           p_serialization_factory,
                       std::string const &p_name);

std::shared_ptr<MsgSubscriber> createMsgSubscriber(
    std::shared_ptr<IPubSubSubscriber> p_subscriber,
    std::shared_ptr<serialization::SerializationFactory>
        p_serialization_factory,
    std::shared_ptr<messages::MessageFactory> p_message_factory);
} // namespace msg
} // namespace lzr

#endif // MESSAGING_BROKER_INC_PUBSUB_FACTORY_H
