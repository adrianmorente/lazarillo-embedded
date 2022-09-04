#ifndef SERIALIZATION_INC_DESERIALIZER_H
#define SERIALIZATION_INC_DESERIALIZER_H

#include <jsoncpp/json/json.h>

namespace serialization
{
/**
 *
 */
class Deserializer
{
public:
    /**
     * Construct a new Deserializer object
     */
    Deserializer();

    Deserializer &setObject(std::string const &p_value);

    std::string object() const;

    template<typename Type> Type extract(std::string const &p_key);

    /**
     * Extracts the specified key from the json. Key is removed from the json
     * object afterwards.
     *
     * Returned value is passed as reference parameter to allow concatenating
     * elements.
     *
     * @tparam Value
     * @param p_key
     * @param p_value
     * @return Deserializer&
     */
    template<typename Value>
    Deserializer &extract(std::string const &p_key, Value const &p_value);

private:
    Json::Value m_value;
};
} // namespace serialization

#endif // SERIALIZATION_INC_DESERIALIZER_H
