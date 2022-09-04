#ifndef MESSAGES_DEFINITION_INC_EVENT_REBOOT_H
#define MESSAGES_DEFINITION_INC_EVENT_REBOOT_H

#include "i_base_message.h"

namespace messages
{
class EventReboot : public IBaseMessage
{
public:
    // Unique name of the message
    static constexpr char const *NAME{"EVENT_CONNECTION_STATUS"};

    explicit EventReboot(serialization::Deserializer &) {}

    serialization::Serializer &
        serializePayload(serialization::Serializer &p_serializer) const final
    {
        return IBaseMessage::serializePayload(p_serializer);
    }

    std::string name() const final { return NAME; }
};
} // namespace messages

#endif // MESSAGES_DEFINITION_INC_EVENT_REBOOT_H
