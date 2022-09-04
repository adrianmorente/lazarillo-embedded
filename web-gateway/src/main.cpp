#include "web-gateway/service.h"

int main(int argc, char *argv[])
{
    lzr::web::Service service(argc, argv);
    return service.run();
}
