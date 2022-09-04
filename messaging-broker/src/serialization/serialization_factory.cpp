#include "messaging-broker/serialization/serialization_factory.h"

using namespace lzr::msg::serialization;

std::unique_ptr<JsonSerializer> SerializationFactory::createSerializer() const
{
    return std::make_unique<JsonSerializer>();
}

std::unique_ptr<JsonDeserializer>
    SerializationFactory::createDeserializer() const
{
    return std::make_unique<JsonDeserializer>();
}
