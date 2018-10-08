#ifndef SESSION_H
#define SESSION_H

#include <iostream>
#include <memory>
#include <vector>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/system/error_code.hpp>

using namespace std;
using namespace boost::asio;

typedef shared_ptr<ip::tcp::socket> socket_ptr;
typedef vector<char> ByteArray;
const size_t BUF_SIZE = 1024;

class session;
typedef shared_ptr<session> session_ptr;

class session : public std::enable_shared_from_this<session>
{
public:
    session(io_service &service);
    virtual ~session();

    ip::tcp::socket& getSocket();
    void start();
    void close();

    void sendData(const string &msg);

private:
    void read_handle(const boost::system::error_code& err);
    void write_handle(const boost::system::error_code& err);

private:
    socket_ptr m_socket;
    char m_readMsg[BUF_SIZE];
};

#endif // SESSION_H
