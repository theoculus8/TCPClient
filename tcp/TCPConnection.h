#pragma once

#include <QSslSocket>
#include <QThread>
#include <QMutex>

class TCPConnection : public QThread
{
    Q_OBJECT
public:
    TCPConnection();
    virtual ~TCPConnection();


    QString getIpAddress();
    int getPort();
    bool isConnected();


public slots:
    void connectToSocket(QString address, int port);
    void writeToSocket(QString s);

    void connected();
    void disconnected();

private:
    QSslSocket* m_socket = Q_NULLPTR;
    QString     m_ipAddress = "";
    int         m_port = -1;
    QMutex      m_mutex;
    bool        m_isConnected = false;
};
