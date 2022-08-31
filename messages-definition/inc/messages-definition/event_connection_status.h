#ifndef MESSAGES_DEFINITION_INC_EVENT_CONNECTION_STATUS_H
#define MESSAGES_DEFINITION_INC_EVENT_CONNECTION_STATUS_H

#include "base_message.h"
#include "models/connection_status.h"

namespace messages
{
class EventConnectionStatus : public IBaseMessage
{
public:
    // Unique name of the message
    static constexpr char const *name{"EVENT_CONNECTION_STATUS"};

    explicit EventConnectionStatus(models::ConnectionStatus p_status)
        : m_status{p_status}
    {
    }

    explicit EventConnectionStatus(serialization::Deserializer &p_deserializer)
    {
        p_deserializer.extract("Status", m_status);
    }

    serialization::Serializer &
        serializePayload(serialization::Serializer &p_serializer) const final
    {
        IBaseMessage::serializePayload(p_serializer);
        return p_serializer.add("Status", m_status);
    }

    std::string name() const final { return name; }

private:
    // Status of the network connection
    models::ConnectionStatus m_status{models::ConnectionStatus::UNKNOWN};
};
} // namespace messages

#endif // MESSAGES_DEFINITION_INC_EVENT_CONNECTION_STATUS_H
