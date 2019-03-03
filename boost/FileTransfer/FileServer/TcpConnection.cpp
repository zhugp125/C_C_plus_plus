#include "TcpConnection.h"
#include "FileData.h"
#include <memory>

TcpConnection::TcpConnection(io_service &service)
    : m_socketPtr(make_shared<tcp::socket>(service))
    , m_readBuffer{0}
{
}

TcpConnection::~TcpConnection()
{
    close();
}

void TcpConnection::start()
{
    memset(m_readBuffer, 0, strlen(m_readBuffer));
    m_socketPtr->async_read_some(buffer(m_readBuffer, BUF_SIZE), std::bind(&TcpConnection::readHandle, shared_from_this(), std::placeholders::_1));
}

void TcpConnection::close()
{
    if (m_socketPtr->is_open())
    {
        m_socketPtr->close();
    }
}

void TcpConnection::sendData(const string &msg)
{
    m_socketPtr->async_write_some(buffer(msg), std::bind(&TcpConnection::writeHandle, shared_from_this(), std::placeholders::_1));
}

void TcpConnection::sendData(const char *msg, const unsigned int len)
{
    m_socketPtr->async_write_some(buffer(msg, len), std::bind(&TcpConnection::writeHandle, shared_from_this(), std::placeholders::_1));
}

void TcpConnection::sendData(const ByteArray &array)
{
    m_socketPtr->async_write_some(buffer(array), std::bind(&TcpConnection::writeHandle, shared_from_this(), std::placeholders::_1));
}

SocketPtr TcpConnection::getSocketPtr() const
{
    return m_socketPtr;
}

void TcpConnection::setNotifyFunc(const NotifyFunc &notify)
{
    m_notify = notify;
}

void TcpConnection::readHandle(const std::error_code &err)
{
    if (!err)
    {
        FileDataPtr pFileData(make_shared<FileData>(FileData::loads(m_readBuffer)));
        m_notify(pFileData);
        start();
    }
    else
    {
        close();
    }
}

void TcpConnection::writeHandle(const std::error_code &err)
{
    if (!err)
    {
    }
    else
    {
        close();
    }
}
