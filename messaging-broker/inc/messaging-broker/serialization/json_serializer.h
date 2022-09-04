#ifndef SERIALIZATION_INC_SERIALIZATION_JSON_SERIALIZER_H
#define SERIALIZATION_INC_SERIALIZATION_JSON_SERIALIZER_H

#include "serialization/serializer.h"

#include "messages-definition/message_header.h"

namespace lzr
{
using serialization::Serializer;
namespace msg
{
namespace serialization
{
class JsonSerializer
{
public:
    JsonSerializer();

    void setHeader(messages::MessageHeader const &p_header);

    Serializer &payload();

    std::string object() const;

private:
    messages::MessageHeader m_header;

    std::unique_ptr<Serializer> m_serializer;
};
} // namespace serialization
} // namespace msg
} // namespace lzr

#endif // SERIALIZATION_INC_SERIALIZATION_JSON_SERIALIZER_H
