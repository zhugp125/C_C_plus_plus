#ifndef TCPSESSION_H
#define TCPSESSION_H

#include "TcpConnection.h"

class TcpSession : public std::enable_shared_from_this<TcpSession>
{
public:
    TcpSession(io_service &service);

    void start();
    void close();

    size_t getOffset() const;
    void addOffset(const size_t offset);

    SocketPtr getSocketPtr() const;

    void sendData(const string& msg);
    void sendData(const char* msg, const unsigned int len);
    void sendData(const ByteArray& array);

    void setNotifyFunc(const NotifyFunc& notify);

private:
    size_t m_offset;
    TcpConnectionPtr m_tcpConnectionPtr;
};

#endif // TCPSESSION_H
