#include "service-base/service_messager.h"

#include "messaging-broker/pubsub/pubsub_factory.h"
#include "messaging-broker/serialization/serialization_factory.h"

using lzr::service::ServiceMessager;

ServiceMessager::ServiceMessager(
    std::shared_ptr<lzr::msg::Broker> p_broker,
    std::shared_ptr<messages::MessageFactory> p_message_factory,
    std::string const &p_service_name)
{
    auto serialization =
        std::make_shared<lzr::msg::serialization::SerializationFactory>();
    m_pub =
        lzr::msg::createMsgPublisher(p_broker, serialization, p_service_name);
    m_sub = lzr::msg::createMsgSubscriber(p_broker, serialization,
                                          p_message_factory);
}

bool ServiceMessager::publish(std::string const &p_topic,
                              messages::IBaseMessage const &p_message)
{
    return m_pub->publish(p_topic, p_message);
}

void ServiceMessager::subscribe(
    std::string const &p_topic, std::string const &p_message,
    std::shared_ptr<lzr::msg::IBaseMessageReceiver> p_receiver)
{
    m_sub->subscribe(p_topic);
    m_sub->add_receiver(p_message, p_receiver);
}
