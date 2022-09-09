#include "web-gateway/service.h"

using lzr::web::Service;

Service::Service(int argc, char *argv[])
    : m_server{new WebsocketServer(8080, this)}
    , m_app{new QCoreApplication(argc, argv)}
{
}

Service::~Service()
{
    delete m_server;
    delete m_app;
}

std::string Service::get_name()
{
    return "web-gateway";
}

void Service::init() {}

int Service::run_internal()
{
    return m_app->exec();
}

void Service::finish() {}
