#include "lazarillo-hmi/service.h"

int main(int argc, char *argv[])
{
    lzr::hmi::Service service(argc, argv);
    service.run();
}
