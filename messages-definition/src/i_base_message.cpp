#include "messages-definition/i_base_message.h"

using messages::IBaseMessage;
using messages::MessageHeader;

void IBaseMessage::setHeader(MessageHeader const &p_header)
{
    m_header = std::make_shared<MessageHeader>(p_header);
}

MessageHeader IBaseMessage::getHeader() const
{
    MessageHeader header;

    // If no header is defined, the default one is returned
    header.name = (m_header) ? m_header.get()->name : header.name;
    return header;
}

serialization::Serializer &
    IBaseMessage::serializePayload(serialization::Serializer &p_serializer) const
{
    return p_serializer;
}
