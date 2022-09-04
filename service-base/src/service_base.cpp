#include "service-base/service_base.h"

#include "messages-definition/factory/message_factory.h"
#include "messaging-broker/pubsub/pubsub_factory.h"
#include "messaging-broker/serialization/serialization_factory.h"

#include <iostream>
#include <systemd/sd-daemon.h>

using lzr::service::ServiceBase;
using namespace std::chrono_literals;

int ServiceBase::run()
{
    // Abstract initialisation for communication
    init_messaging();

    // Initialisation steps given by child class
    init();

    std::cout << "Running service " << get_name() << std::endl;
    sd_notify(0, "READY=1");

    auto exit_code = run_internal();

    std::cout << "Stopping service " << get_name() << std::endl;
    sd_notify(0, "STOPPED=1");

    return exit_code;
}

bool ServiceBase::publish(std::string const &p_topic,
                          messages::IBaseMessage const &p_message)
{
    return m_messager->publish(p_topic, p_message);
}

void ServiceBase::subscribe(std::string const &p_topic,
                            std::string const &p_message,
                            std::shared_ptr<lzr::msg::IBaseMessageReceiver> p_receiver)
{
    m_messager->subscribe(p_topic, p_message, p_receiver);
}

void ServiceBase::init_messaging()
{
    // Create auxiliar broker that implements pub and sub needs
    auto broker = std::shared_ptr<lzr::msg::Broker>();

    constexpr auto CONNECTION_TIMEOUT{5s};
    auto const connected = broker->connect_async(CONNECTION_TIMEOUT).get();
    if (!connected)
    {
        throw std::runtime_error("Unable to connect to broker.");
    }

    auto message_factory = std::make_shared<messages::MessageFactory>();

    m_messager = std::make_shared<lzr::service::ServiceMessager>(
        broker, message_factory, get_name());
}
