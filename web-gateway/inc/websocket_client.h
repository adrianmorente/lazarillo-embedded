#ifndef LZR_WEB_GATEWAY_WEBSOCKET_CLIENT_H
#define LZR_WEB_GATEWAY_WEBSOCKET_CLIENT_H

#include <QObject>
#include <QTimer>
#include <QWebSocket>

class WebsocketClient : public QObject
{
    Q_OBJECT
public:
    explicit WebsocketClient(const QUrl &p_url, QObject *p_parent = nullptr);

private slots:
    void connected();
    void disconnected();
    void messageReceived(QString p_message);
    void heartbeat();

signals:
    void closed();

private:
    // Socket that holds the actual connection
    QWebSocket m_socket;

    // Timer for emitting a heartbeat periodically
    QTimer m_timer;
};

#endif // LZR_WEB_GATEWAY_WEBSOCKET_CLIENT_H
