#include "serialization/deserializer.h"

#include <iostream>

using serialization::Deserializer;

Deserializer::Deserializer() {}

template<typename Type> Type Deserializer::extract(std::string const &p_key)
{
    Type value{};
    extract(p_key, value);
    return value;
}

template<typename Value>
Deserializer &Deserializer::extract(std::string const &p_key,
                                    Value const &p_value)
{
    auto show_error_message = [p_key]()
    {
        std::cout << "ERROR: Couldn't read " << p_key << " from Json."
                  << std::endl;
    };

    try
    {
        auto field = m_value[p_key];

        if (!field.isNull())
        {
            p_value = field.asString();
            m_value.removeMember(p_key);
            return *this;
        }
        else
        {
            show_error_message();
        }
    }
    catch (Json::LogicError const &e)
    {
        show_error_message();
    }
}
