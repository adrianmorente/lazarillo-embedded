#ifndef MESSAGING_BROKER_INC_REDIS_DISPATCHER_H
#define MESSAGING_BROKER_INC_REDIS_DISPATCHER_H

#include "messaging-broker/pubsub/raw_messages/i_raw_data_processor.h"
#include "messaging-broker/pubsub/raw_messages/i_raw_data_receiver.h"

#include "serialization/serialization_factory.h"

#include <mutex>
#include <unordered_map>

namespace lzr
{
namespace msg
{
/**
 * Class to dispatch the messages received.
 *
 * Raw data receivers are used for reading messages directly from the transport
 * layer and handle them internally.
 */
class RedisDispatcher : public IRawDataReceiver
{
public:
    RedisDispatcher(
        std::shared_ptr<serialization::SerializationFactory> p_factory);

    bool registerMessageReceiver(std::string const &p_callback,
                                 std::shared_ptr<IRawDataProcessor> p_receiver);

    bool addMessageReceiver(std::string const &p_name,
                            std::string const &p_message_id,
                            std::shared_ptr<IRawDataProcessor> p_receiver);

    void registerRawDataReceiver(std::shared_ptr<IRawDataReceiver> p_receiver);

    bool onRawData(std::string const &p_topic,
                   std::string const &p_value) override;

private:
    std::shared_ptr<serialization::SerializationFactory> m_factory;

    // Map of tagged receivers.
    // First string shall be the subscribed message.
    // Second map will hold each receiver indexed by receiver's name.
    std::unordered_map<
        std::string,
        std::unordered_map<std::string, std::shared_ptr<IRawDataProcessor>>>
        m_receivers;
    std::mutex m_mutex;

    // List of raw data receivers that perform on the transport layer data
    std::vector<std::shared_ptr<IRawDataReceiver>> m_raw_receivers;
};
} // namespace msg
} // namespace lzr

#endif // MESSAGING_BROKER_INC_REDIS_DISPATCHER_H
