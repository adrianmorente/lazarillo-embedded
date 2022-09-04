#ifndef MESSAGING_BROKER_INC_PUBSUB_RECEIVER_WORKER_H
#define MESSAGING_BROKER_INC_PUBSUB_RECEIVER_WORKER_H

#include "i_message_receiver.h"

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

namespace lzr
{
namespace msg
{
class ReceiverWorker
{
public:
    ReceiverWorker(std::string const &p_worker_id);

    ~ReceiverWorker();

    void enqueue(std::shared_ptr<IBaseMessageReceiver> p_receiver,
                 std::string const &p_topic,
                 std::shared_ptr<messages::IBaseMessage> p_message);

private:
    struct WorkerData
    {
        WorkerData(std::shared_ptr<IBaseMessageReceiver> p_receiver,
                   std::string const &p_topic,
                   std::shared_ptr<messages::IBaseMessage> p_message)
            : receiver{std::move(p_receiver)}
            , topic{std::move(p_topic)}
            , message{std::move(p_message)}
        {
        }

        std::shared_ptr<IBaseMessageReceiver> receiver;
        std::string topic;
        std::shared_ptr<messages::IBaseMessage> message;
    };

    void worker_thread();

    std::condition_variable m_cv;
    std::mutex m_mutex;
    bool m_terminate{false};
    std::queue<WorkerData> m_queue;
    std::string m_worker_id;
    std::thread m_thread;
};
} // namespace msg
} // namespace lzr

#endif // MESSAGING_BROKER_INC_PUBSUB_RECEIVER_WORKER_H
