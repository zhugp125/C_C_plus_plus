#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include <cstring>
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>

using namespace std;
using namespace boost::asio;

io_service g_service;
ip::tcp::endpoint g_endpoint(ip::tcp::v4(), 8888);
ip::tcp::acceptor g_acceptor(g_service, g_endpoint);
io_service::strand g_strand(g_service);

typedef shared_ptr<ip::tcp::socket> socket_ptr;
typedef vector<char> ByteArray;

const size_t BUF_SIZE = 1024;

void recvData(const socket_ptr&);
void connect_handle(const boost::system::error_code&, const socket_ptr&);

void write_handle(const boost::system::error_code& err)
{
    if (!err)
    {
        cout << "on data send" << endl;
    }
}

void sendData(const socket_ptr& sock, const string& msg)
{
    ByteArray data;
    data.resize(msg.size());
    memcpy(&data[0], msg.c_str(), msg.size());

    sock->async_write_some(buffer(data, data.size()), std::bind(&write_handle, std::placeholders::_1));
}

void closeServer()
{
    g_acceptor.close();
    g_service.stop();
}

void read_handle(const boost::system::error_code& err, const char* data, const socket_ptr& sock)
{
    if (!err)
    {
        string msg(data);
        if (msg != "q")
        {
            cout << "from client size: " << msg.size() << " data: " << msg << endl;
            g_strand.post(std::bind(&recvData, sock));
        }
        else
        {
            cout << "end" << endl;
            sendData(sock, "end");
            //g_strand.post(std::bind(&closeServer));
        }
    }
}

void recvData(const socket_ptr& pSock)
{
    char data[BUF_SIZE] = {0};
    pSock->async_read_some(buffer(data, BUF_SIZE), std::bind(&read_handle, std::placeholders::_1, data, pSock));
}

void addConnect()
{
    socket_ptr pSock(new ip::tcp::socket(g_service));
    g_acceptor.async_accept(*pSock, std::bind(&connect_handle, std::placeholders::_1, pSock));
}

void connect_handle(const boost::system::error_code& err, const socket_ptr& sock)
{
    if (!err)
    {
        cout << "connect, address: " << sock->remote_endpoint().address().to_string() << endl;
        g_strand.post(std::bind(&recvData, sock));
        addConnect();
    }
}

int main()
{
    try
    {
        socket_base::keep_alive keepAlive(true);
        g_acceptor.set_option(keepAlive);

        addConnect();
        g_service.run();
    }
    catch(const std::exception& e)
    {
        cout << e.what() << endl;
    }
    cout << "Hello world" << endl;
    return 0;
}
