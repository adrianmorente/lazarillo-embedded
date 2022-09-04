#ifndef MESSAGING_BROKER_INC_PUBSUB_RAW_MESSAGES_I_RAW_DATA_RECEIVER_H
#define MESSAGING_BROKER_INC_PUBSUB_RAW_MESSAGES_I_RAW_DATA_RECEIVER_H

#include <string>

namespace lzr
{
namespace msg
{
class IRawDataReceiver
{
public:
    virtual bool onRawData(std::string const &p_topic,
                           std::string const &p_value)
    {
        (void)p_topic;
        (void)p_value;
        return false;
    }
};
} // namespace msg
} // namespace lzr

#endif // MESSAGING_BROKER_INC_PUBSUB_RAW_MESSAGES_I_RAW_DATA_RECEIVER_H
