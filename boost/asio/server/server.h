#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include <cstring>
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>

using namespace std;
using namespace boost::asio;

typedef shared_ptr<ip::tcp::socket> socket_ptr;
typedef vector<char> ByteArray;

const size_t BUF_SIZE = 1024;

class server
{
public:
    server(io_service& service, ip::tcp::endpoint ep);

private:
    void addConnect();

    void connect_handle(const boost::system::error_code& err, const socket_ptr& sock);
    void recvData(const socket_ptr& sock);

    void read_handle(const boost::system::error_code& err, const char* data, const socket_ptr& sock);

    void sendData(const socket_ptr& sock, const string& msg);
    void write_handle(const boost::system::error_code& err);

private:
    io_service& m_service;
    ip::tcp::acceptor m_acceptor;
    io_service::strand m_strand;
};

#endif // SERVER_H
