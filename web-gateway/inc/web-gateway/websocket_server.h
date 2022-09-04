#ifndef LZR_WEB_GATEWAY_WEBSOCKET_CLIENT_H
#define LZR_WEB_GATEWAY_WEBSOCKET_CLIENT_H

#include <QObject>
#include <QTimer>
#include <QWebSocket>
#include <QWebSocketServer>

/**
 * Wrapper of a Qt's framework Websocket server class.
 *
 * Allows to hold a WS server and to receive the corresponding signals without
 * having to implement all the protocol logic.
 */
class WebsocketServer : public QObject
{
    Q_OBJECT

public:
    explicit WebsocketServer(const int p_port  = 8080,
                             QObject *p_parent = nullptr);

private slots:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();

signals:
    void closed();

private:
    // Socket that holds the actual connection
    QWebSocketServer *m_socket;

    // Timer for emitting a heartbeat periodically
    QTimer m_timer;
};

#endif // LZR_WEB_GATEWAY_WEBSOCKET_CLIENT_H
