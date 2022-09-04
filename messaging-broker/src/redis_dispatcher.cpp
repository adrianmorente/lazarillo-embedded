#include "messaging-broker/redis_dispatcher.h"

#include <algorithm>
#include <iostream>

using lzr::msg::RedisDispatcher;
using lzr::msg::serialization::SerializationFactory;

RedisDispatcher::RedisDispatcher(
    std::shared_ptr<SerializationFactory> p_factory)
    : m_factory{std::move(p_factory)}
{
}

bool RedisDispatcher::registerMessageReceiver(
    std::string const &p_callback,
    std::shared_ptr<IRawDataProcessor> p_receiver)
{
    return addMessageReceiver(std::string{}, p_callback, std::move(p_receiver));
}

bool RedisDispatcher::addMessageReceiver(
    std::string const &p_name, std::string const &p_message_id,
    std::shared_ptr<IRawDataProcessor> p_receiver)
{
    bool result{false};
    std::lock_guard<std::mutex> lock{m_mutex};

    // Find the subscribed receivers for the given message id
    auto message_receivers = m_receivers.find(p_message_id);
    if (message_receivers == m_receivers.end())
    {
        // Add new level to map indexed by the id of the message
        std::tie(message_receivers, std::ignore) =
            m_receivers.insert({p_message_id, {}});
    }

    auto &receivers = message_receivers->second;
    auto const iter = receivers.find(p_name);
    if (iter == receivers.end())
    {
        // Insert new processor indexed by requested name
        receivers.insert({p_name, std::move(p_receiver)});
        result = true;
    }

    return result;
}

void RedisDispatcher::registerRawDataReceiver(
    std::shared_ptr<IRawDataReceiver> p_receiver)
{
    std::lock_guard<std::mutex> lock{m_mutex};
    m_raw_receivers.emplace_back(std::move(p_receiver));
}

bool RedisDispatcher::onRawData(std::string const &p_topic,
                                std::string const &p_value)
{
    std::lock_guard<std::mutex> lock{m_mutex};

    try
    {
        bool blocked =
            std::any_of(m_raw_receivers.rbegin(), m_raw_receivers.rend(),
                        [&p_topic, &p_value](auto receiver)
                        { return receiver->onRawData(p_topic, p_value); });

        if (blocked)
            return true;

        // If not blocked, create deserializer for reading the data
        auto deserializer = m_factory->createDeserializer();
        deserializer->setObject(p_value, p_topic);

        auto const &header = deserializer->getHeader();
        auto receiver      = m_receivers.find(header.name);

        if (receiver != m_receivers.end())
        {
            auto &payload = deserializer->payload();
            for (auto processor : receiver->second)
            {
                processor.second->process(payload, p_topic, header);
            }

            return true;
        }

        throw std::runtime_error{"No processor was found."};
    }
    catch (std::exception const &e)
    {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    return true;
}
