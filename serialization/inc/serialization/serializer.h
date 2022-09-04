#ifndef SERIALIZATION_INC_SERIALIZER_H
#define SERIALIZATION_INC_SERIALIZER_H

#include <jsoncpp/json/json.h>
#include <memory>
#include <string>

namespace serialization
{
/**
 * Serializer class that defines the format for handling Json objects.
 */
class Serializer
{
public:
    /**
     * Construct a new Serializer object
     */
    Serializer();

    /**
     * Content of the json as string
     *
     * @return std::string
     */
    std::string get_content() const
    {
        Json::StreamWriterBuilder builder;
        return Json::writeString(builder, m_value);
    }

    /**
     * Writes the content of the json
     *
     * @param p_value
     * @return Serializer&
     */
    Serializer &set_content(Json::Value const &p_value)
    {
        m_value = p_value;
        return *this;
    }

    /**
     * Checks if the json object is empty
     *
     * @return bool true if the json is empty
     */
    bool empty() const { return m_value.empty(); }

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

protected:
    // Json object where the data is stored
    Json::Value m_value;
};
} // namespace serialization

#endif // SERIALIZATION_INC_SERIALIZER_H
