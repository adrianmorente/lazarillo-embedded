#ifndef MESSAGES_DEFINITION_INC_TOPICS_H
#define MESSAGES_DEFINITION_INC_TOPICS_H

#include <string>

namespace messages
{
namespace topics
{
/**
 * List of messaging topics where services publish to and read from.
 *
 * TODO: Instead of putting all of them together here, they could be splitted by
 * service.
 */

static std::string const LAZARILLO_HMI_CMD_TOPIC   = "/lzr/hmi/cmd";
static std::string const LAZARILLO_HMI_EVENT_TOPIC = "/lzr/hmi/event";
static std::string const MOTOR_MANAGER_CMD_TOPIC   = "/lzr/motor/cmd";
static std::string const MOTOR_MANAGER_EVENT_TOPIC = "/lzr/motor/event";
static std::string const WEB_GATEWAY_CMD_TOPIC     = "/lzr/web/cmd";
static std::string const WEB_GATEWAY_EVENT_TOPIC   = "/lzr/web/event";
} // namespace topics
} // namespace messages

#endif // MESSAGES_DEFINITION_INC_TOPICS_H