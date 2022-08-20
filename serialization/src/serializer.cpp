#include "serialization/serializer.h"

#include <jsoncpp/json/writer.h>

using serialization::Serializer;

Serializer::Serializer() {}

template<typename Value>
Serializer &Serializer::add(std::string const &p_key, Value const &p_value)
{
    m_value[p_key] = p_value;
    return *this;
}
