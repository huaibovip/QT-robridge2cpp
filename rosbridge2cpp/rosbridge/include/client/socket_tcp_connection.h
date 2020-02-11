#pragma once

#include <iostream>
#include <string>
#include <iomanip>

#include "rapidjson/document.h"

#include "types.h"
#include "helper.h"
#include "messages/rosbridge_msg.h"
//#include "itransport_layer.h"

#include <QUrl>
#include <QObject>
#include <QWebSocket>

using json = rapidjson::Document;

namespace rosbridge2cpp{
class SocketTCPConnection : public QObject
{
    Q_OBJECT

public:
    SocketTCPConnection () = default;
    ~SocketTCPConnection ();

    enum MessageCode {TEXT, BINARY};

    bool Init(QUrl p_ip_addr);
    bool SendTextMessage(const QString &message);
    bool sendBinaryMessage(const QByteArray &data);
    void RegisterIncomingMessageCallback(std::function<void(json&)> fun);
    void RegisterErrorCallback(std::function<void(QAbstractSocket::SocketError)> fun);
    void ReportError(QAbstractSocket::SocketError err);

private:
    QUrl ip_addr_;
    QWebSocket connect_to_;
    bool callback_function_defined_ = false;
    std::function<void(json&)> incoming_message_callback_;
    std::function<void(QAbstractSocket::SocketError)> error_callback_ = nullptr;

signals:
    void newMessageReceived(int msg_code);
    void newDisconnected();

public slots:
    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(const QString &message);
    void onBinaryMessageReceived(const QByteArray &message);
};
}
