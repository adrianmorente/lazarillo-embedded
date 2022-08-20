#ifndef SERIALIZATION_INC_I_SERIALIZER_H
#define SERIALIZATION_INC_I_SERIALIZER_H

#include <jsoncpp/json/json.h>
#include <memory>
#include <string>

namespace serialization
{
/**
 * Interface that serves for creating serializers and deserializers, defining
 * common behaviour as the contained Json object, methods for reading it and
 * checking emptiness.
 */
class ISerializer
{
public:
    virtual ~ISerializer() = 0;

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
     * @return ISerializer&
     */
    ISerializer &set_content(Json::Value const &p_value)
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

protected:
    // Json object where the data is stored
    Json::Value m_value;
};
} // namespace serialization

#endif // SERIALIZATION_INC_I_SERIALIZER_H
