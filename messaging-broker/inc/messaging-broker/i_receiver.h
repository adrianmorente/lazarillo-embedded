#ifndef MESSAGING_BROKER_INC_I_RECEIVER_H
#define MESSAGING_BROKER_INC_I_RECEIVER_H

#include <string>

namespace lzr
{
namespace msg
{
class IReceiver
{
public:
    virtual ~IReceiver() {}

    /**
     * Callback when a message is received.
     *
     * Message is received as string and then deserialized.
     *
     * @param p_topic topic where the message was published
     * @param p_message serialized message
     */
    virtual void on_receive(std::string const &p_topic,
                            std::string const &p_message) = 0;
};
} // namespace msg
} // namespace lzr

#endif // MESSAGING_BROKER_INC_I_RECEIVER_H
