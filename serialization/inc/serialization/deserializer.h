#ifndef SERIALIZATION_INC_DESERIALIZER_H
#define SERIALIZATION_INC_DESERIALIZER_H

#include "i_serializer.h"

namespace serialization
{
/**
 *
 */
class Deserializer : public ISerializer
{
public:
    /**
     * Construct a new Deserializer object
     */
    Deserializer();

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
};
} // namespace serialization

#endif // SERIALIZATION_INC_DESERIALIZER_H
