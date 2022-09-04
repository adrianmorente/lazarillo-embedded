#include "messaging-broker/pubsub/msg_subscriber.h"
#include "messaging-broker/pubsub/i_pub_sub_subscriber.h"
#include "messaging-broker/serialization/serialization_factory.h"

#include <algorithm>
#include <iostream>
#include <vector>

using lzr::msg::MsgSubscriber;

MsgSubscriber::MsgSubscriber(
    std::shared_ptr<lzr::msg::IPubSubSubscriber> p_subscriber,
    std::shared_ptr<messages::MessageFactory> p_message_factory,
    std::shared_ptr<serialization::SerializationFactory>
        p_serialization_factory)
    : m_subscriber{p_subscriber}
    , m_message_factory{p_message_factory}
    , m_serialization_factory{p_serialization_factory}
{
}

void MsgSubscriber::subscribe(std::string const &p_topic)
{
    m_subscriber->subscribe(p_topic);
}

void MsgSubscriber::unsubscribe(std::string const &p_topic)
{
    m_subscriber->unsubscribe(p_topic);
}

std::vector<std::string> MsgSubscriber::get_subscribed_topics()
{
    return m_subscriber->get_subscribed_topics();
}

void MsgSubscriber::add_receiver(
    std::string const &p_message_name,
    std::shared_ptr<IBaseMessageReceiver> p_receiver,
    std::string const &p_callback_id, std::string const &p_worker_id)
{
    std::lock_guard<std::mutex> lock{m_receivers_mutex};

    auto iter = m_receivers.find(p_message_name);
    if (iter == m_receivers.end())
    {
        // Make tuple reserving space for worker in second place
        std::tie(iter, std::ignore) = m_receivers.insert({p_message_name, {}});
    }

    auto &receivers     = iter->second;
    auto const callback = receivers.find(p_callback_id);
    if (callback == receivers.end())
    {
        receivers.insert({p_callback_id, {p_worker_id, std::move(p_receiver)}});

        auto worker = m_workers.find(p_worker_id);
        if (worker == m_workers.end())
        {
            m_workers.insert(
                {p_worker_id, std::make_shared<ReceiverWorker>(p_worker_id)});
        }
    }
    else
    {
        throw std::logic_error{"Callback with the id " + p_callback_id +
                               " already exists."};
    }
}

void MsgSubscriber::remove_receiver(std::string const &p_message_name,
                                    std::string const &p_callback_id)
{
    std::lock_guard<std::mutex> lock{m_receivers_mutex};

    // Search callback by message name
    auto iter = m_receivers.find(p_message_name);
    if (iter == m_receivers.end())
    {
        throw std::logic_error{"Callback for message " + p_message_name +
                               " not found."};
    }

    // Search callback by callback id
    auto &receivers = iter->second;
    auto receiver   = receivers.find(p_callback_id);
    if (receiver == receivers.end())
    {
        throw std::logic_error{"Callback for message " + p_message_name +
                               " and callback id " + p_callback_id +
                               " not found."};
    }

    // Finally remove the receiver
    receivers.erase(receiver);
    if (receivers.empty())
    {
        // If the removed callback was the last one in the worker, worker should
        // be also removed
        m_receivers.erase(iter);
    }
}

std::vector<MsgSubscriber::WorkerData>
    MsgSubscriber::get_receivers(std::string const &p_message_name) const
{
    std::lock_guard<std::mutex> lock{m_receivers_mutex};

    std::vector<MsgSubscriber::WorkerData> receivers;

    auto receiver = m_receivers.find(p_message_name);
    if (receiver != m_receivers.end())
    {
        std::transform(begin(receiver->second), end(receiver->second),
                       back_inserter(receivers),
                       [](auto const &iter) { return std::get<1>(iter); });
    }

    return receivers;
}

void MsgSubscriber::on_receive(std::string const &p_topic,
                               std::string const &p_message)
{
    std::cout << "Received message from " << p_topic << std::endl;

    auto deserializer = m_serialization_factory->createDeserializer();

    try
    {
        deserializer->setObject(p_message, p_topic);
    }
    catch (std::exception const &e)
    {
        std::cout << "Exception while deserializing message: " << e.what()
                  << std::endl;
        return;
    }

    auto header       = deserializer->getHeader();
    auto message_name = header.name;
    auto message =
        m_message_factory->make(message_name, deserializer->payload());
    message->setHeader(header);

    // Loop over receivers list to find callbacks of the requested message
    auto receivers = get_receivers(message_name);
    if (receivers.empty())
    {
        std::cout << "Receiver not found for message " << message_name
                  << std::endl;
        return;
    }

    // Enqueue workers for the requested callback
    {
        std::lock_guard<std::mutex> lock{m_receivers_mutex};
        for (auto &&receiver : receivers)
        {
            auto worker = m_workers.find(receiver.worker_id);
            if (worker == end(m_workers))
            {
                std::cout << "Worker " << receiver.worker_id << " not found."
                          << std::endl;
                return;
            }
            worker->second->enqueue(receiver.receiver, p_topic, message);
        }
    }
}
