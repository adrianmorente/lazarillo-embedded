#include "messaging-broker/serialization/json_serializer.h"

#include "lazarillo-utils/datetime.h"

using lzr::msg::serialization::JsonSerializer;
using serialization::Serializer;

JsonSerializer::JsonSerializer() {}

void JsonSerializer::setHeader(messages::MessageHeader const &p_header)
{
    m_header = p_header;
}

Serializer &JsonSerializer::payload()
{
    return *m_serializer;
}

std::string JsonSerializer::object() const
{
    Serializer header, full_payload;

    // Compose header
    header.add("message_id", m_header.name);
    if (!m_header.source.empty())
    {
        header.add("source", m_header.source);
    }
    header.add("timestamp", utils::to_string(m_header.timestamp));

    // Compose full message
    full_payload.add("header", header);
    if (!m_serializer->empty())
    {
        full_payload.add("body", *m_serializer);
    }

    return full_payload.get_content();
}
