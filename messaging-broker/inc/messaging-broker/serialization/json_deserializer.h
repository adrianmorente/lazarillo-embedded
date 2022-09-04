#ifndef SERIALIZATION_INC_SERIALIZATION_JSON_DESERIALIZER_H
#define SERIALIZATION_INC_SERIALIZATION_JSON_DESERIALIZER_H

#include "messages-definition/message_header.h"
#include "serialization/deserializer.h"

namespace lzr
{
using serialization::Deserializer;
namespace msg
{
namespace serialization
{
class JsonDeserializer
{
public:
    JsonDeserializer();

    /**
     * @brief Fills the deserialized data.
     *
     * @param p_data
     * @param p_topic
     */
    void setObject(std::string const &p_data, std::string const &p_topic);

    messages::MessageHeader getHeader() const;

    Deserializer &payload() const;

private:
    messages::MessageHeader m_header;

    std::unique_ptr<Deserializer> m_deserializer;
};
} // namespace serialization
} // namespace msg
} // namespace lzr

#endif // SERIALIZATION_INC_SERIALIZATION_JSON_DESERIALIZER_H