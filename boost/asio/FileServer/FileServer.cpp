#include "FileServer.h"
#include <boost/bind.hpp>
#include <iostream>

FileServer::FileServer(io_service &io)
    : m_ios(io)
    , m_acceptor(m_ios, ip::tcp::endpoint(ip::tcp::v4(), 6688))
{
    start();
}

void FileServer::start()
{
    sock_pt sock(new ip::tcp::socket(m_ios));
    m_acceptor.async_accept(*sock, bind(&FileServer::accept_handle, this, placeholdes::error, sock));
}

void FileServer::accept_handle(const system::error_code &ec, FileServer::sock_pt sock)
{
    if (ec)
    {
        return ;
    }

    std::cout << "client address: ";
    std::cout << sock->remote_endpoint().address().to_string() << std::endl;
    sock->async_write_some(buffer("hello asio"), bind(&FileServer::write_handle, this, placeholdes::error));

    start();
}

void FileServer::write_handle(const system::error_code &ec)
{
    std::cout << "send msg complete..." << std::endl;
}
