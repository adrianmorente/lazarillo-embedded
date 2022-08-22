#include "service-base/service_base.h"

#include <iostream>

using utils::ServiceBase;

std::string ServiceBase::get_name()
{
    return m_name;
}

void ServiceBase::run()
{
    std::cout << "Running service " << get_name() << std::endl;
    sd_notify(0, "READY=1");

    run_private();

    std::cout << "Stopping service " << get_name() << std::endl;
    sd_notify(0, "STOPPED=1");
}