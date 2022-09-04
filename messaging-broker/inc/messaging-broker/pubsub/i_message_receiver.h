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
class IBaseMessageReceiver
{
public:
    virtual ~IBaseMessageReceiver() {}

    /**
     * Method called when a message is received if the class is registered as
     * callback.
     *
     * Must be implemented by message receivers.
     *
     * @param p_message
     */
    virtual void
        onMessage(std::string const &p_topic,
                  std::shared_ptr<messages::IBaseMessage> p_message) = 0;
};

/**
 * Overrides the IBaseMessageReceiver class to provide the actual message name
 * in the callback.
 */
template<typename MessageName>
class IMessageReceiver : public IBaseMessageReceiver
{
public:
    /**
     * @copydoc IBaseMessageReceiver::onMessage calling actual name instead of
     * IBaseMessage
     */
    virtual void onMessage(std::shared_ptr<MessageName> p_message) = 0;

private:
    void onMessage(std::string const &p_topic,
                   std::shared_ptr<messages::IBaseMessage> p_message) override
    {
        (void)p_topic;

        auto typed = std::dynamic_pointer_cast<MessageName>(p_message);

        if (typed)
        {
            onMessage(std::move(typed));
        }
        else
        {
            throw std::runtime_error{"Couldn't cast message type."};
        }
    }
};
} // namespace msg
} // namespace lzr

#endif // MESSAGING_BROKER_INC_I_MSG_RECEIVER_H
