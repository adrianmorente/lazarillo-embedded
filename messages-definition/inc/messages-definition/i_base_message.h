#ifndef MESSAGES_DEFINITION_INC_I_BASE_MESSAGE_H
#define MESSAGES_DEFINITION_INC_I_BASE_MESSAGE_H

#include "message_header.h"

#include "serialization/deserializer.h"
#include "serialization/serializable.h"
#include "serialization/serializer.h"

namespace messages
{
/**
 * Class to be inherited for implementing new messages.
 *
 * The header is serialized automatically to contain the message name.
 *
 * The payload is left to be implemented by children.
 *
 * std::string name() const must be overriden to contain the actual message
 * name.
 */
class IBaseMessage : public serialization::Serializable
{
public:
    /**
     * Destroy the Base Message object
     *
     */
    ~IBaseMessage() {}

    /**
     * Returns the unique name of the implemented message
     *
     * @return std::string
     */
    virtual std::string name() const = 0;

    /**
     * Set the Header object
     *
     * @param header
     */
    void setHeader(MessageHeader const &p_header);

    /**
     * Get the Header object
     *
     * @return MessageHeader
     */
    MessageHeader getHeader() const;

    /**
     * Get the Default Header object (if no header has been set)
     *
     * @return MessageHeader
     */
    MessageHeader getDefaultHeader() const;

    /**
     * Serializes the internal payload of the message.
     *
     * @param p_serializer Serializer to export the whole data
     * @return serialization::Serializer& Same serializer but containing the
     * serialized data
     */
    virtual serialization::Serializer &
        serializePayload(serialization::Serializer &p_serializer) const = 0;

    /**
     * @copydoc Serializable::serialize(serialization::Serializer &)
     */
    serialization::Serializer &
        serialize(serialization::Serializer &p_serializer) const override
    {
        return serializePayload(p_serializer);
    }

private:
    // Header of the message
    std::shared_ptr<MessageHeader> m_header;
};
} // namespace messages

#endif // MESSAGES_DEFINITION_INC_I_BASE_MESSAGE_H
