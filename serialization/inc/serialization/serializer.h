#ifndef SERIALIZATION_INC_SERIALIZER_H
#define SERIALIZATION_INC_SERIALIZER_H

#include "i_serializer.h"

namespace serialization
{
/**
 * Serializer class that defines the format for handling Json objects.
 */
class Serializer : public ISerializer
{
public:
    /**
     * Construct a new Serializer object
     */
    Serializer();

    /**
     * Adds a new field to the Json message. Returning the reference to the
     * object itself eases concatenating elements (when there are many fields in
     * a message).
     *
     * @param p_key
     * @param value
     * @return Serializer&
     */
    template<typename Value>
    Serializer &add(std::string const &p_key, Value const &p_value);
};
} // namespace serialization

#endif // SERIALIZATION_INC_SERIALIZER_H
