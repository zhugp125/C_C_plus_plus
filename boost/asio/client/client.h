#ifndef CLIENT_H
#define CLIENT_H

#include <deque>
#include <memory>
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>

using namespace std;
using namespace boost::asio;

typedef shared_ptr<ip::tcp::socket> socket_ptr;
const size_t BUF_SIZE = 1024;

class client
{
public:
    client(io_service& service, ip::tcp::endpoint ep);
    virtual ~client();

    void sendData(const string& msg);
    void close();

private:
    void connect_handle(const boost::system::error_code& err);
    void write_handle(const boost::system::error_code& err);
    void read_handle(const boost::system::error_code& err);

    void do_sendData(const string& msg);
    void do_close();

    void recvData();

private:
    io_service& m_service;
    socket_ptr m_socket;
    char m_readMsg[BUF_SIZE];
    deque<string> m_writeMsgs;
};

#endif // CLIENT_H
