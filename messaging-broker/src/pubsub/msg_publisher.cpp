#include "messaging-broker/pubsub/msg_publisher.h"

#include "lazarillo-utils/datetime.h"
#include "messaging-broker/serialization/json_serializer.h"

#include <iostream>

using lzr::msg::MsgPublisher;

MsgPublisher::MsgPublisher(std::shared_ptr<IPubSubPublisher> p_publisher,
                           std::shared_ptr<serialization::SerializationFactory>
                               p_serialization_factory,
                           std::string const &p_name)
    : m_publisher{std::move(p_publisher)}
    , m_serialization_factory{(std::move(p_serialization_factory))}
    , m_name{p_name}
{
}

bool MsgPublisher::publish(std::string const &p_topic,
                           messages::IBaseMessage const &p_message)
{
    std::unique_ptr<serialization::JsonSerializer> serializer =
        m_serialization_factory->createSerializer();

    messages::MessageHeader header = p_message.getHeader();
    header.source                  = m_name;
    header.timestamp               = utils::now();
    serializer->setHeader(header);

    try
    {
        p_message.serializePayload(serializer->payload());
    }
    catch (const std::exception &e)
    {
        std::cout << "Error trying to serialize message " << m_name
                  << std::endl;
        return false;
    }

    return m_publisher->publish(p_topic, serializer->object());
}
