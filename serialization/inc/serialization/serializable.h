#ifndef SERIALIZATION_INC_SERIALIZABLE_H
#define SERIALIZATION_INC_SERIALIZABLE_H

#include "serializer.h"

namespace serialization
{
/**
 * Interface to define the required methods for serializing a message.
 */
class Serializable
{
    /**
     * Serializes the object using the Serializer object.
     *
     * @param p_serializer
     * @return Serializer& Reference to the serializer with the added content.
     */
    virtual Serializer &serialize(Serializer &p_serializer) const = 0;
};
} // namespace serialization

#endif // SERIALIZATION_INC_SERIALIZABLE_H
