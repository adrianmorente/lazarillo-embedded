#include <QCoreApplication>

#include "web-gateway/websocket_server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    auto server{new WebsocketServer(8080)};
    // QObject::connect(server, &WebsocketServer::closed, &a,
    // &QCoreApplication::quit);

    return a.exec();
}
