#include "event_reboot_receiver.h"

using lzr::hmi::EventRebootReceiver;

EventRebootReceiver::EventRebootReceiver() {}

void EventRebootReceiver::onMessage(
    std::shared_ptr<messages::EventReboot> p_message)
{
    // TODO: terminate service and reboot
    (void)p_message;
}
