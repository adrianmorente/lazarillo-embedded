#include "messaging-broker/pubsub/receiver_worker.h"

#include <iostream>

using lzr::msg::ReceiverWorker;

ReceiverWorker::ReceiverWorker(std::string const &p_worker_id)
    : m_worker_id{p_worker_id}
{
    m_thread = std::thread{&ReceiverWorker::worker_thread, this};
}

ReceiverWorker::~ReceiverWorker()
{
    {
        std::unique_lock<std::mutex> lock{m_mutex};
        m_terminate = true;
        m_cv.notify_all();
    }

    m_thread.join();
}

void ReceiverWorker::enqueue(std::shared_ptr<IBaseMessageReceiver> p_receiver,
                             std::string const &p_topic,
                             std::shared_ptr<messages::IBaseMessage> p_message)
{
    std::unique_lock<std::mutex> lock{m_mutex};
    m_queue.emplace(std::move(p_receiver), std::move(p_topic),
                    std::move(p_message));
    m_cv.notify_all();
}

void ReceiverWorker::worker_thread()
{
    std::unique_lock<std::mutex> lock{m_mutex};
    while (!m_terminate)
    {
        m_cv.wait(lock);

        // Consume all the messages in the queue
        while (!m_queue.empty())
        {
            WorkerData data = std::move(m_queue.front());
            m_queue.pop();
            lock.unlock();

            auto const &message_name = data.message->getHeader().name;

            try
            {
                // Callbacks the inherited onMessage method
                data.receiver->onMessage(data.topic, data.message);
                std::cout << m_worker_id << " read " << message_name
                          << std::endl;
            }
            catch (...)
            {
                std::cout << "Uncaught exception while processing message."
                          << std::endl;
            }

            lock.lock();
        }
    }
}
