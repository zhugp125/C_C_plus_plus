#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

#include "TcpCommon.h"

using namespace boost::asio;
using namespace boost::asio::ip;

typedef shared_ptr<tcp::socket> SocketPtr;

constexpr int BUF_SIZE = 64 * 1024 * 1024;

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
public:
    TcpConnection(io_service& service);
    virtual ~TcpConnection();

    void start();
    void close();

    void sendData(const string& msg);
    void sendData(const char* msg, const unsigned int len);
    void sendData(const ByteArray& array);

    SocketPtr getSocketPtr() const;

    void setNotifyFunc(const NotifyFunc& notify);

private:
    void readHandle(const std::error_code& err);
    void writeHandle(const std::error_code& err);

private:
    SocketPtr m_socketPtr;
    char m_readBuffer[BUF_SIZE];

    NotifyFunc m_notify;
};

#endif // TCPCONNECT_H
