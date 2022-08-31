#include "service-base/service_base.h"

#include <iostream>
#include <systemd/sd-daemon.h>

using lzr::service::ServiceBase;

void ServiceBase::run()
{
    std::cout << "Running service " << get_name() << std::endl;
    sd_notify(0, "READY=1");

    run_internal();

    std::cout << "Stopping service " << get_name() << std::endl;
    sd_notify(0, "STOPPED=1");
}

bool ServiceBase::publish(std::string const &p_topic,
                          std::string const &p_message)
{
    return m_broker->publish(p_topic, p_message);
}

bool ServiceBase::subscribe(std::string const &p_topic,
                            std::string const &p_message,
                            std::shared_ptr<msg::IMsgReceiver> p_receiver)
{
    m_broker->subscribe(p_topic);
    m_broker->add_receiver(p_message, std::move(p_receiver));
}

void ServiceBase::init_messaging() {}
