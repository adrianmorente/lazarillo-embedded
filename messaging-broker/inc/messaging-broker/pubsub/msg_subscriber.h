#ifndef MESSAGING_BROKER_INC_MSG_SUBSCRIBER_H
#define MESSAGING_BROKER_INC_MSG_SUBSCRIBER_H

#include "i_message_receiver.h"
#include "i_pub_sub_subscriber.h"
#include "receiver_worker.h"

#include "messages-definition/factory/message_factory.h"
#include "messages-definition/i_base_message.h"

#include <string>
#include <vector>

namespace lzr
{
namespace msg
{
class MsgSubscriber
{
public:
    static constexpr auto DEFAULT_CALLBACK_ID = "CALLBACK";
    static constexpr auto DEFAULT_WORKER_ID   = "WORKER";

    struct WorkerData
    {
        std::string worker_id;
        std::shared_ptr<IBaseMessageReceiver> receiver;
    };

    MsgSubscriber(std::shared_ptr<IPubSubSubscriber> p_subscriber,
                  std::shared_ptr<messages::MessageFactory> p_message_factory,
                  std::shared_ptr<serialization::SerializationFactory>
                      p_serialization_factory);

    ~MsgSubscriber() {}

    /**
     * Subscribes the broker to a pubsub topic
     *
     * @param p_topic
     */
    void subscribe(std::string const &p_topic);

    /**
     * Unsubscriber the broker from a topic
     *
     * @param p_topic
     */
    void unsubscribe(std::string const &p_topic);

    /**
     * @brief Get the subscribed topics object
     *
     * @return std::vector<std::string>
     */
    std::vector<std::string> get_subscribed_topics();

    /**
     * Registers a callback for incoming messages.
     *
     * @param p_message_name
     * @param p_receiver
     * @param p_callback_id
     */
    void add_receiver(std::string const &p_message_name,
                      std::shared_ptr<IBaseMessageReceiver> p_receiver,
                      std::string const &p_callback_id = DEFAULT_CALLBACK_ID,
                      std::string const &p_worker_id   = DEFAULT_WORKER_ID);

    /**
     * Unregisters callback from message.
     *
     * @param p_message_name
     * @param p_callback_id
     */
    void remove_receiver(std::string const &p_message_name,
                         std::string const &p_callback_id);

    /**
     * Get the receiver callbacks associated to a message
     *
     * @param p_message_name
     * @return std::vector<WorkerData>
     */
    std::vector<WorkerData>
        get_receivers(std::string const &p_message_name) const;

    template<typename MessageReceiver>
    void add_receiver(std::shared_ptr<MessageReceiver> p_receiver,
                      std::string const &p_callback_id = DEFAULT_CALLBACK_ID,
                      std::string const &p_worker_id   = DEFAULT_WORKER_ID)
    {
        add_receiver(MessageReceiver::MessageType::NAME, p_receiver,
                     p_callback_id, p_worker_id);
    }

    /**
     * Callback triggered when a message is received.
     *
     * @param p_topic
     * @param p_message
     */
    void on_receive(std::string const &p_topic, std::string const &p_message);

private:
    std::shared_ptr<IPubSubSubscriber> m_subscriber;
    std::shared_ptr<messages::MessageFactory> m_message_factory;
    std::shared_ptr<serialization::SerializationFactory>
        m_serialization_factory;

    // First level of the map is the name of the message
    // Mapped by the message name, there's a map of workers indexed by the
    // receiver's name
    std::unordered_map<std::string, std::unordered_map<std::string, WorkerData>>
        m_receivers;

    // Map the actual message workers by worker_id (id present in the second
    // level of the map above)
    std::unordered_map<std::string, std::shared_ptr<ReceiverWorker>> m_workers;
    mutable std::mutex m_receivers_mutex;
};
} // namespace msg
} // namespace lzr

#endif // MESSAGING_BROKER_INC_MSG_SUBSCRIBER_H
