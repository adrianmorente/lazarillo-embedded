#ifndef SERVICE_BASE_INC_SERVICE_BASE_H
#define SERVICE_BASE_INC_SERVICE_BASE_H

#include "service_messager.h"

#include "messages-definition/i_base_message.h"
#include "messaging-broker/pubsub/msg_publisher.h"
#include "messaging-broker/pubsub/msg_subscriber.h"

#include <string>

namespace lzr
{
namespace service
{
class ServiceBase
{
public:
    /**
     * Returns the name of the service
     */
    virtual std::string get_name() = 0;

    /**
     * Does all the initialization tasks on start
     */
    virtual void init() = 0;

    /**
     * Runs the service blocking until ending.
     *
     * @return exit code of the service
     */
    int run();

    /**
     * Abstract run method called by @ref run(). Intended to be implemented by
     * children.
     */
    virtual int run_internal() = 0;

    /**
     * Terminates the service. Blocks until run returns
     */
    virtual void finish() = 0;

    /**
     * @copydoc Broker::publish
     */
    bool publish(std::string const &p_topic,
                 messages::IBaseMessage const &p_message);

    /**
     * @copydoc Broker::subscribe
     */
    void subscribe(std::string const &p_topic, std::string const &p_message,
                   std::shared_ptr<msg::IBaseMessageReceiver> p_receiver);

private:
    /**
     * Private method used for initializing the messaging context, used by
     * inheriting children.
     */
    void init_messaging();

    // Messaging broker. Allows to publish and to subscribe to messages
    std::shared_ptr<ServiceMessager> m_messager;
};
} // namespace service
} // namespace lzr

#endif // SERVICE_BASE_INC_SERVICE_BASE_H
