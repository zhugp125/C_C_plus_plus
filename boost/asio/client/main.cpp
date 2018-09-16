#include <iostream>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/system/error_code.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind/bind.hpp>

using namespace std;
using namespace boost::asio;

io_service service;
ip::tcp::socket sock(service);

void connect(const string& addr, const size_t port)
{
    ip::tcp::endpoint ep(ip::address::from_string(addr), port);
    boost::system::error_code error;
    sock.connect(ep, error);
}

void connect_handler(const boost::system::error_code& err)
{
    if (err)
    {
        cout << "connect failed" << endl;
        return ;
    }
}

void asyncConnect(const string& addr, const size_t port)
{
    ip::tcp::endpoint (ip::address::from_string(addr), port);
    sock.async_connect(ep, boost::bind(connect_handler, _1));
}

void sendData(const string& msg)
{
    cout << "send data size = ";
    cout << sock.write_some(buffer(msg)) << endl;
}

void reciveData()
{
    while (true)
    {
        size_t len = sock.available();
        if (len > 0)
        {
            char data[len + 1];
            memset(data, 0, len + 1);
            boost::system::error_code error;
            sock.read_some(buffer(data, len), error);
            cout << data << endl;
        }
    }
}

int main()
{
    /*
    connect("127.0.0.1", 2001);
    sendData("hello asio");

    boost::thread t(boost::bind(reciveData));
    t.join();
    */

    asyncConnect("127.0.0.1", 2001);
    service.run();

    cout << "Hello World!" << endl;
    return 0;
}
