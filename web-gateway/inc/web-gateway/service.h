#ifndef WEB_GATEWAY_INC_SERVICE_H
#define WEB_GATEWAY_INC_SERVICE_H

#include "websocket_server.h"

#include "service-base/service_base.h"

#include <QCoreApplication>

namespace lzr
{
namespace web
{
class Service : public lzr::service::ServiceBase
{
public:
    Service(int argc, char *argv[]);

    ~Service() override;

    std::string get_name() override;

    void init() override;

    int run_internal() override;

    void finish() override;

private:
    // Holds the real Qt console application
    QCoreApplication *m_app;

    // Holds the Websocket server
    WebsocketServer *m_server;
};
} // namespace web
} // namespace lzr

#endif // WEB_GATEWAY_INC_SERVICE_H
