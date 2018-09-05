#include "FileClient.h"
#include <boost/bind.hpp>
#include <iostream>

FileClient::FileClient(io_service &ios)
    : m_ios(ios)
    , m_ep(ip::address::from_string("127.0.0.1"), 6688)
    , m_sock(new ip::tcp::socket(m_ios))
{
    start();
}

void FileClient::start()
{
    m_sock->async_connect(m_ep, bind(&FileClient::conn_handle, this, boost::asio::placeholders::error));
}

void FileClient::conn_handle(const system::error_code &ec)
{
    if (ec)
    {
        return ;
    }

    std::cout << "recive from " << m_sock->remote_endpoint().address().to_string() << std::endl;
    vec_char str(new std::vector<char>(100, 0));

    m_sock->async_read_some(buffer(*str), bind(&FileClient::read_handle, this, boost::asio::placeholders::error, str));
}

void FileClient::read_handle(const system::error_code &ec, FileClient::vec_char pstr)
{
    if (ec)
    {
        return ;
    }

    std::string str(pstr->begin(), pstr->end());

}

void FileClient::write_handle(const system::error_code &ec)
{
    if (ec)
    {
        return ;
    }
}
