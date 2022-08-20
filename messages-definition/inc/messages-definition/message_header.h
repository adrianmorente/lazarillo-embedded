#ifndef MESSAGES_DEFINITION_INC_MESSAGE_HEADER_H
#define MESSAGES_DEFINITION_INC_MESSAGE_HEADER_H

#include "lazarillo-utils/datetime.h"

#include <string>

namespace messages
{
struct MessageHeader
{
    // Name of the message
    std::string name{"DEFAULT_NAME"};

    // Name of the service that sent the message
    std::string source{"SERVICE"};

    // Timestamp when the message is sent
    utils::Datetime timestamp;
};
} // namespace messages

#endif // MESSAGES_DEFINITION_INC_MESSAGE_HEADER_H
