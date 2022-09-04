#include "messages-definition/factory/message_factory.h"

#include "messages-definition/event_connection_status.h"
#include "messages-definition/event_reboot.h"

using namespace messages;

MessageFactory::MessageFactory()
{
    registerMessageFactory<EventConnectionStatus>();
    registerMessageFactory<EventReboot>();
}

std::shared_ptr<messages::IBaseMessage>
    MessageFactory::make(std::string const &p_message_id,
                         serialization::Deserializer &p_deserializer)
{
    auto const pos = m_messages.find(p_message_id);

    if (pos != m_messages.cend())
    {
        return pos->second(p_deserializer);
    }

    return std::shared_ptr<messages::IBaseMessage>{};
}

template<typename MessageName> void MessageFactory::registerMessageFactory()
{
    m_messages.emplace(std::string{MessageName::NAME},
                       [](serialization::Deserializer &p_deserializer) {
                           return std::make_unique<MessageName>(p_deserializer);
                       });
}
