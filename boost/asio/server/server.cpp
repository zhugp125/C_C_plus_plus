#include "server.h"

server::server(io_service& service, ip::tcp::endpoint ep)
    :m_service(service)
    ,m_acceptor(service, ep)
    ,m_strand(service)
{
    socket_base::keep_alive keepAlive(true);
    m_acceptor.set_option(keepAlive);

    addConnect();
}

void server::addConnect()
{
    socket_ptr sock(new ip::tcp::socket(m_service));
    m_acceptor.async_accept(*sock, std::bind(&server::connect_handle, this, std::placeholders::_1, sock));
}

void server::connect_handle(const boost::system::error_code &err, const socket_ptr &sock)
{
    if (!err)
    {
        cout << "connect, address: " << sock->remote_endpoint().address().to_string() << endl;
        m_strand.post(std::bind(&server::recvData, this, sock));
        addConnect();
    }
}

void server::recvData(const socket_ptr &sock)
{
    char data[BUF_SIZE] = {0};
    sock->async_read_some(buffer(data, BUF_SIZE), std::bind(&server::read_handle, this, std::placeholders::_1, data, sock));
}

void server::read_handle(const boost::system::error_code &err, const char *data, const socket_ptr &sock)
{
    if (!err)
    {
        string msg(data);
        cout << "from client size: " << msg.size() << " data: " << msg << endl;
        m_strand.post(std::bind(&server::recvData, this, sock));
        sendData(sock, msg);
    }
}

void server::sendData(const socket_ptr &sock, const string &msg)
{
    sock->async_write_some(buffer(msg), std::bind(&server::write_handle, this, std::placeholders::_1));
}

void server::write_handle(const boost::system::error_code &err)
{
    if (!err)
    {
        //cout << "on data send" << endl;
    }
}
