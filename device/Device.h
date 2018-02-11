////////////////////////////////////////////////////////////
/// device.h
///
/// Copyright Jeremiah Pope 2017
////////////////////////////////////////////////////////////

#pragma once

#include <QTcpSocket>
#include "tcp/TcpConnection.h"

class Device : public QObject
{
    Q_OBJECT

signals:
    void connectToDevice(QString address, int port);
    void sendCommand(QString json);

public:
    void remoteConnect(const QString& address, int port);
    bool isDeviceConnected();
    void startVideoStream();

protected:
    Device();
    virtual ~Device();

    void writeJsonToSocket(const QJsonArray& json);

    QThread* m_thread;
    TCPConnection m_conn;
};
