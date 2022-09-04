#ifndef LAZARILLO_HMI_SRC_MESSAGE_RECEIVERS_EVENT_REBOOT_RECEIVER_H
#define LAZARILLO_HMI_SRC_MESSAGE_RECEIVERS_EVENT_REBOOT_RECEIVER_H

#include "messages-definition/event_reboot.h"
#include "messaging-broker/pubsub/i_message_receiver.h"

namespace lzr
{
namespace hmi
{
class EventRebootReceiver : public msg::IMessageReceiver<messages::EventReboot>
{
public:
    EventRebootReceiver();

    void onMessage(std::shared_ptr<messages::EventReboot> p_message) override;
};
} // namespace hmi
} // namespace lzr

#endif // LAZARILLO_HMI_SRC_MESSAGE_RECEIVERS_EVENT_REBOOT_RECEIVER_H
