#ifndef MESSAGES_DEFINITION_INC_MESSAGE_FACTORY_MESSAGE_FACTORY_H
#define MESSAGES_DEFINITION_INC_MESSAGE_FACTORY_MESSAGE_FACTORY_H

#include "messages-definition/i_base_message.h"
#include "serialization/deserializer.h"

#include <functional>
#include <string>
#include <unordered_map>

namespace messages
{
/**
 * Common place for listing all the messages that take place in the system.
 */
class MessageFactory
{
public:
    using MessageFunction =
        std::function<std::shared_ptr<messages::IBaseMessage>(
            serialization::Deserializer &)>;

    /**
     * @brief Construct a new Message Factory object
     */
    MessageFactory();

    /**
     * Creates abstract message type from string id.
     *
     * @param p_message_id
     * @param p_deserializer
     * @return std::shared_ptr<messages::IBaseMessage>
     */
    std::shared_ptr<messages::IBaseMessage>
        make(std::string const &p_message_id,
             serialization::Deserializer &p_deserializer);

    /**
     * Appends message type to map of messages
     *
     * @tparam MessageName
     */
    template<typename MessageName> void registerMessageFactory();

private:
    std::unordered_map<std::string, MessageFunction> m_messages;
};
} // namespace messages

#endif // MESSAGES_DEFINITION_INC_MESSAGE_FACTORY_MESSAGE_FACTORY_H
