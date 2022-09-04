#ifndef MESSAGING_BROKER_INC_PUBSUB_RAW_MESSAGES_I_RAW_DATA_PROCESSOR_H
#define MESSAGING_BROKER_INC_PUBSUB_RAW_MESSAGES_I_RAW_DATA_PROCESSOR_H

#include "messages-definition/message_header.h"
#include "serialization/deserializer.h"

#include <string>

namespace lzr
{
using serialization::Deserializer;

namespace msg
{
class IRawDataProcessor
{
public:
    virtual ~IRawDataProcessor() {}

    virtual void process(Deserializer &p_deserializer,
                         std::string const &p_topic,
                         messages::MessageHeader const &p_header) = 0;
};
} // namespace msg
} // namespace lzr

#endif // MESSAGING_BROKER_INC_PUBSUB_RAW_MESSAGES_I_RAW_DATA_PROCESSOR_H
