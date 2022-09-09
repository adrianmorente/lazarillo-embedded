#include "web-gateway/websocket_server.h"

#include "messages-definition/event_reboot.h"
#include "topics/topics.h"

#include <QDebug>

using lzr::web::WebsocketServer;

WebsocketServer::WebsocketServer(const int p_port, lzr::web::Service *p_service,
                                 QObject *p_parent)
    : QObject{p_parent}
    , m_service{p_service}
    , m_socket(new QWebSocketServer(QStringLiteral("Lazarillo WS Server"),
                                    QWebSocketServer::NonSecureMode, this))
{
    if (m_socket->listen(QHostAddress::Any, p_port))
    {
        qDebug() << "Listening on port: " << p_port;

        connect(m_socket, &QWebSocketServer::newConnection, this,
                &WebsocketServer::onNewConnection);

        connect(m_socket, &QWebSocketServer::closed, this,
                &WebsocketServer::closed);
    }
}

void WebsocketServer::onNewConnection()
{
    QWebSocket *client = m_socket->nextPendingConnection();

    // Connect socket's signals to method (for each new connection)
    connect(client, &QWebSocket::textMessageReceived, this,
            &WebsocketServer::processTextMessage);
    connect(client, &QWebSocket::binaryMessageReceived, this,
            &WebsocketServer::processBinaryMessage);
    connect(client, &QWebSocket::disconnected, this,
            &WebsocketServer::socketDisconnected);

    qDebug() << "Client connected.";
    client->sendTextMessage(
        QString::fromUtf8("Connection accepted from Websocket server"));
}

void WebsocketServer::processTextMessage(QString p_message)
{
    // auto client{qobject_cast<QWebSocket *>(sender())};
    qDebug() << "Text message received: " << p_message;

    // parse and publish message to other services in web's topic
    if (p_message == "REBOOT")
    {
        m_service->publish(messages::topics::WEB_GATEWAY_EVENT_TOPIC,
                           messages::EventReboot{});
    }
    // else if (p_message == "OTHER_ACTION")
    // {
    //     // send other message related to OTHER_ACTION
    // }
}

void WebsocketServer::processBinaryMessage(QByteArray p_message) {}

void WebsocketServer::socketDisconnected()
{
    // auto client{qobject_cast<QWebSocket *>(sender())};
    qDebug() << "Client disconnected.";
}
