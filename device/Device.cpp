////////////////////////////////////////////////////////////
/// device.cpp
///
/// Copyright Jeremiah Pope 2017
////////////////////////////////////////////////////////////

#include <QJsonDocument>
#include "Device.h"

Device::Device()
{    
    m_thread = new QThread();
    connect(this, &Device::connectToDevice, &m_conn, &TCPConnection::connectToSocket);
    connect(this, &Device::sendCommand, &m_conn, &TCPConnection::writeToSocket);

    m_conn.moveToThread(m_thread);
    m_thread->start();
}

Device::~Device()
{
    m_thread->quit();
    m_thread->wait();
    delete m_thread;
}

void Device::remoteConnect(const QString& address, int port)
{
    emit connectToDevice(address, port);
}

bool Device::isDeviceConnected()
{
    return m_conn.isConnected();
}

void Device::writeJsonToSocket(const QJsonArray& json)
{
    if (isDeviceConnected())
    {
        QJsonDocument doc(json);
        QString s = doc.toJson(QJsonDocument::Compact);
        //qDebug() << "writing: " << s;
        emit sendCommand(s);
    }
}
