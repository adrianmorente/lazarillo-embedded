#include <QCoreApplication>

#include "inc/websocket_client.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    WebsocketClient socket(QUrl("ws://localhost:8080"));
    QObject::connect(&socket, &WebsocketClient::closed,
                     [=]() { qDebug() << "Socket closed"; });

    return a.exec();
}
