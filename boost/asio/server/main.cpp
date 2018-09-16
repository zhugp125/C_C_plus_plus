#include <iostream>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/system/error_code.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind/bind.hpp>

using namespace std;
using namespace boost::asio;

typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;
io_service service;
ip::tcp::endpoint ep(ip::tcp::v4(), 2001);
ip::tcp::acceptor acc(service, ep);

void client_session(socket_ptr sock)
{
    while (true)
    {
        size_t len = sock->available();
        if (len > 0)
        {
            char data[len + 1];
            memset(data, 0, len + 1);
            boost::system::error_code error;
            sock->read_some(buffer(data, len), error);
            cout << data << endl;
            sock->write_some(buffer("ok", 2), error);
        }
    }
}

void start()
{
    while (true)
    {
        socket_ptr sock(new ip::tcp::socket(service));
        boost::system::error_code error;
        acc.accept(*sock, error);
        if (!error)
        {
            cout << "ok" << endl;
        }
        boost::thread(boost::bind(client_session, sock));
    }
}

void start_accept();

void handle_accept(socket_ptr sock, const boost::system::error_code& err)
{
    if (err)
    {
        return;
    }

    ip::tcp::endpoint ep = sock->remote_endpoint();
    cout << ep.address().to_string() << ":" << ep.port() << endl;
    start_accept();
}

void start_accept()
{
    socket_ptr sock(new ip::tcp::socket(service));
    acc.async_accept(*sock, boost::bind(handle_accept, sock, _1));
}

int main()
{
    //start();

    start_accept();
    service.run();

    cout << "Hello World!" << endl;
    return 0;
}
