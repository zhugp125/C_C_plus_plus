#include "FileClient.h"
#include <boost/bind.hpp>
#include <iostream>

FileClient::FileClient(io_service &ios)
    : m_ios(ios)
    , m_ep(ip::address::from_string("127.0.0.1"), 6688)
{
    start();
}

void FileClient::start()
{
    sock_pt sock(new ip::tcp::socket(m_ios));
    sock->async_connect(m_ep, bind(&FileClient::conn_handle, this, placeholdes::error, sock));
}

void FileClient::conn_handle(const system::error_code &ec, FileClient::sock_pt sock)
{
    if (ec)
    {
        return ;
    }

    std::cout << "recive from " << sock->remote_endpoint().address().to_string() << std::endl;
    vec_char str(new std::vector<char>(100, 0));

    sock->async_read_some(buffer(*str), bind(&FileClient::read_handle, this, placeholdes::error, str));
    start();
}

void FileClient::read_handle(const system::error_code &ec, FileClient::vec_char str)
{
    if (ec)
    {
        return ;
    }

    std::cout << &(*str)[0] << std::endl;
}
