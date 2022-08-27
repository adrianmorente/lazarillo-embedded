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

void ServiceBase::init_messaging() {}
