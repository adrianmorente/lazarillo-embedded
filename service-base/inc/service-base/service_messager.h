#ifndef SERVICE_BASE_INC_SERVICE_MESSAGER_H
#define SERVICE_BASE_INC_SERVICE_MESSAGER_H

#include "messages-definition/i_base_message.h"
#include "messaging-broker/broker.h"
#include "messaging-broker/pubsub/i_message_receiver.h"
#include "messaging-broker/pubsub/msg_publisher.h"
#include "messaging-broker/pubsub/msg_subscriber.h"

namespace lzr
{
namespace service
{
class ServiceMessager
{
public:
    ServiceMessager(std::shared_ptr<lzr::msg::Broker> p_broker,
                    std::shared_ptr<messages::MessageFactory> p_message_factory,
                    std::string const &p_service_name);

    bool publish(std::string const &p_topic,
                 messages::IBaseMessage const &p_message);

    void subscribe(std::string const &p_topic, std::string const &p_message,
                   std::shared_ptr<lzr::msg::IBaseMessageReceiver> p_receiver);

    auto get_pub() const { return m_pub; }
    auto get_sub() const { return m_sub; }

private:
    std::shared_ptr<lzr::msg::MsgPublisher> m_pub;
    std::shared_ptr<lzr::msg::MsgSubscriber> m_sub;
};
} // namespace service
} // namespace lzr

#endif // SERVICE_BASE_INC_SERVICE_MESSAGER_H
