#include "messaging-broker/serialization/json_deserializer.h"
#include "messaging-broker/serialization/serialization_factory.h"

using lzr::msg::serialization::JsonDeserializer;
using serialization::Deserializer;

JsonDeserializer::JsonDeserializer() {}

void JsonDeserializer::setObject(std::string const &p_data,
                                 std::string const &p_topic)
{
    (void)p_topic;

    std::unique_ptr<Deserializer> header, body, full;
    full->setObject(p_data);
    full->extract("header", header);
    full->extract("payload", body);

    header->extract("name", m_header.name);
    header->extract("source", m_header.source);
    header->extract("timestamp", m_header.timestamp);
}

messages::MessageHeader JsonDeserializer::getHeader() const
{
    return m_header;
}

Deserializer &JsonDeserializer::payload() const
{
    return *m_deserializer;
}
