#include "messages-definition/base_message.h"

using messages::BaseMessage;
using messages::MessageHeader;

void BaseMessage::setHeader(MessageHeader const &p_header)
{
    m_header = std::make_shared<MessageHeader>(p_header);
}

MessageHeader BaseMessage::getHeader() const
{
    MessageHeader header;

    // If no header is defined, the default one is returned
    header.name = (m_header) ? m_header.get()->name : header.name;
    return header;
}

serialization::Serializer &
    BaseMessage::serializePayload(serialization::Serializer &p_serializer) const
{
    return p_serializer;
}
