#ifndef MESSAGES_DEFINITION_INC_MODELS_CONNECTION_STATUS_H
#define MESSAGES_DEFINITION_INC_MODELS_CONNECTION_STATUS_H

namespace messages
{
namespace models
{
enum class ConnectionStatus
{
    UNKNOWN       = 0,
    NOT_CONNECTED = 1,
    CONNECTED     = 2
};
}
} // namespace messages

#endif // MESSAGES_DEFINITION_INC_MODELS_CONNECTION_STATUS_H
