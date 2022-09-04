#ifndef MESSAGING_BROKER_INC_SERIALIZATION_SERIALIZATION_FACTORY_H
#define MESSAGING_BROKER_INC_SERIALIZATION_SERIALIZATION_FACTORY_H

#include "json_deserializer.h"
#include "json_serializer.h"

namespace lzr
{
namespace msg
{
namespace serialization
{
/**
 * Class used for generating serializer and deserializers.
 *
 * Right now only Json is used, but this could be easily turned into factory
 * pattern returning Serializer interfaces and Deserializer interfaces
 * implementing different types instead of Json type.
 */
class SerializationFactory
{
public:
    std::unique_ptr<JsonSerializer> createSerializer() const;

    std::unique_ptr<JsonDeserializer> createDeserializer() const;
};
} // namespace serialization
} // namespace msg
} // namespace lzr

#endif // MESSAGING_BROKER_INC_SERIALIZATION_SERIALIZATION_FACTORY_H
