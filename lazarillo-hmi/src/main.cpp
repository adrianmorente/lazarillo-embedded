#include "lazarillo-hmi/service.h"

#include "service-base/service_base.h"

int main(int argc, char *argv[])
{
    auto service =
        std::make_shared<lzr::hmi::Service>(argc, argv);
    service->run();
}
