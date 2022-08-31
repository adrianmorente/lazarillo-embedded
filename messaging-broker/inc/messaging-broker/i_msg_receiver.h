#ifndef MESSAGING_BROKER_INC_I_MSG_RECEIVER_H
#define MESSAGING_BROKER_INC_I_MSG_RECEIVER_H

#include "messages-definition/i_base_message.h"

namespace lzr
{
namespace msg
{
/**
 * Interface that must be implemented by any class that wants to be registered
 * as a message's callback.
 */
class IMsgReceiver
{
public:
    virtual ~IMsgReceiver() {}

    /**
     * Method called when a message is received if the class is registered as
     * callback.
     *
     * Must be implemented by message receivers.
     *
     * @param p_message
     */
    virtual void
        on_message(std::shared_ptr<messages::IBaseMessage> p_message) = 0;
};
} // namespace msg
} // namespace lzr

#endif // MESSAGING_BROKER_INC_I_MSG_RECEIVER_H
