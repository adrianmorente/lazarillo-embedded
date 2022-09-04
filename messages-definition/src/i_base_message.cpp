#include "messages-definition/i_base_message.h"

using messages::IBaseMessage;
using messages::MessageHeader;

void IBaseMessage::setHeader(MessageHeader const &p_header)
{
    m_header = std::make_shared<MessageHeader>(p_header);
}

MessageHeader IBaseMessage::getHeader() const
{
    // If no header is defined, the default one is returned
    return (m_header) ? *m_header : getDefaultHeader();
}

MessageHeader IBaseMessage::getDefaultHeader() const
{
    MessageHeader header;
    header.name = name();
    return header;
}

serialization::Serializer &IBaseMessage::serializePayload(
    serialization::Serializer &p_serializer) const
{
    return p_serializer;
}
