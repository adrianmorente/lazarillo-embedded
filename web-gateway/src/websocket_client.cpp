#include "inc/websocket_client.h"

#include <QDebug>

WebsocketClient::WebsocketClient(const QUrl &p_url, QObject *p_parent)
    : QObject{p_parent}
{
    // [Dis]Connection signals
    connect(&m_socket, &QWebSocket::connected, this,
            &WebsocketClient::connected);
    connect(&m_socket, &QWebSocket::disconnected, this,
            &WebsocketClient::disconnected);

    // Slot for showing last error message
    connect(&m_socket,
            QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),
            [=](QAbstractSocket::SocketError error) {
                qDebug() << "Error occurred: " << error << ": "
                         << m_socket.errorString();
            });

    m_socket.open(QUrl(p_url));
}

void WebsocketClient::connected()
{
    qDebug() << "Websocket connected.";

    // Connection for entrying messages
    connect(&m_socket, &QWebSocket::textMessageReceived, this,
            &WebsocketClient::messageReceived);

    // Connection for heartbeat timer
    connect(&m_timer, &QTimer::timeout, this, &WebsocketClient::heartbeat);
    m_timer.start(30000);
}

void WebsocketClient::disconnected()
{
    qDebug() << "Websocket disconnected.";
    m_timer.stop();
}

void WebsocketClient::messageReceived(QString p_message)
{
    qDebug() << "Message received: " << p_message;
}

void WebsocketClient::heartbeat()
{
    qDebug() << "Heartbeat sent.";
    m_socket.ping();
}
