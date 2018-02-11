#include <QFile>
#include <QDir>
#include "TCPConnection.h"

TCPConnection::TCPConnection()
{
    connect(m_socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

TCPConnection::~TCPConnection()
{
    delete m_socket;
}

void TCPConnection::connected()
{
    QMutexLocker lock(&m_mutex);

    qDebug() << "Connected!";
    m_isConnected = true;
}

void TCPConnection::disconnected()
{
    QMutexLocker lock(&m_mutex);

    qDebug() << "Disconnected!";
    m_isConnected = false;
}

void TCPConnection::connectToSocket(QString address, int port)
{
    QMutexLocker lock(&m_mutex);

    m_ipAddress = address;
    m_port = port;

    qDebug() << "Connecting...";

    if (!m_socket)
    {
        m_socket = new QSslSocket(this);

        const char* sslCertificate =
            #include "certificate/server.crt"
        ;

        QList<QSslCertificate> cert = QSslCertificate::fromData(QByteArray(sslCertificate));
        QSslError selfSignedCertificateError(QSslError::SelfSignedCertificate, cert.at(0));
        QSslError hostNameMismatchError(QSslError::HostNameMismatch, cert.at(0));

        QList<QSslError> expectedSslErrors;
        expectedSslErrors.append(selfSignedCertificateError);
        expectedSslErrors.append(hostNameMismatchError);

        m_socket->ignoreSslErrors(expectedSslErrors);

        m_socket->setProtocol(QSsl::SecureProtocols);
    }

    m_socket->connectToHostEncrypted(m_ipAddress, m_port);

    if (!m_socket->waitForEncrypted())
    {
        qDebug() << "error: "<< m_socket->errorString();
        delete m_socket;
        m_socket = Q_NULLPTR;
    }
    else
    {
        m_isConnected = true;
        qDebug() << "Connected";
    }
}

void TCPConnection::writeToSocket(QString s)
{
    QMutexLocker lock(&m_mutex);

    qDebug() << "Sending: " << s;
    m_socket->write(s.toLatin1().data());
}

QString TCPConnection::getIpAddress()
{
    return m_ipAddress;
}

int TCPConnection::getPort()
{
    return m_port;
}

bool TCPConnection::isConnected()
{
    return m_isConnected;
}
