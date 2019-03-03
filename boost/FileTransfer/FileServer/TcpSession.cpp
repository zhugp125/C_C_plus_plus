#include "TcpSession.h"

TcpSession::TcpSession(io_service &service)
    : m_offset(0)
    , m_tcpConnectionPtr(make_shared<TcpConnection>(service))
{
}

void TcpSession::start()
{
    m_tcpConnectionPtr->start();
}

void TcpSession::close()
{
    m_tcpConnectionPtr->close();
}

size_t TcpSession::getOffset() const
{
    return m_offset;
}

void TcpSession::addOffset(const size_t offset)
{
    m_offset += offset;
}

SocketPtr TcpSession::getSocketPtr() const
{
    return m_tcpConnectionPtr->getSocketPtr();
}

void TcpSession::sendData(const string &msg)
{
    m_tcpConnectionPtr->sendData(msg);
}

void TcpSession::sendData(const char *msg, const unsigned int len)
{
    m_tcpConnectionPtr->sendData(msg, len);
}

void TcpSession::sendData(const ByteArray &array)
{
    m_tcpConnectionPtr->sendData(array);
}

void TcpSession::setNotifyFunc(const NotifyFunc &notify)
{
    m_tcpConnectionPtr->setNotifyFunc(notify);
}
