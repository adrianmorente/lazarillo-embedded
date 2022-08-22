#include "lazarillo-hmi/service.h"
#include "lazarillo-hmi/utils/style.h"

using lzr::utils::Style;

int main(int argc, char *argv[])
{
    auto service =
        std::make_shared<utils::ServiceBase>("lazarillo-hmi", argc, argv);
    service->run();
}
