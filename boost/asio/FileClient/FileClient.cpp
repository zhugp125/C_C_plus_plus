#include "FileClient.h"
#include <boost/bind.hpp>
#include <iostream>
#include "../common/common.h"

FileClient::FileClient(io_service &ios)
    : m_ios(ios)
    , m_ep(ip::address::from_string("127.0.0.1"), 59000)
    , m_sock(new ip::tcp::socket(m_ios))
    , m_timer(ios, boost::posix_time::microseconds(500))
{
    start();
    //m_timer.async_wait(boost::bind(&FileClient::on_connected, this, boost::asio::placeholders::error));
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
    vec_char str(new std::vector<char>(200, 0));
    m_sock->async_read_some(buffer(*str), bind(&FileClient::read_handle, this, boost::asio::placeholders::error, str));
}

void FileClient::read_handle(const system::error_code &ec, vec_char pstr)
{
    if (ec)
    {
        return ;
    }

    std::string str(pstr->begin(), pstr->end());
    //std::cout << str << std::endl;
    if (str == g_end)
    {
        m_of.close();
        m_sock->close();
        std::cout << "close" << std::endl;
    }
    else
    {
        MessageInfo info(str);
        if (info.getHeader() == MT_Header)
        {
            m_of.open(info.getFileName(), std::ios_base::app);
            m_fileSize = info.getFileSize();
            m_md5 = info.getFileMd5();
            m_curSize = 0;

            std::cout << info.getFileName() << std::endl;
            std::cout << info.getFileMd5() << std::endl;
            m_sock->async_write_some(buffer(g_begin), bind(&FileClient::write_handle, this, boost::asio::placeholders::error));

            vec_char vec(new std::vector<char>(1400, 0));
            m_sock->async_read_some(buffer(*vec), bind(&FileClient::read_handle, this, boost::asio::placeholders::error, vec));
        }
        else if (info.getHeader() == MT_File && m_curSize < m_fileSize)
        {
            std::string msg = info.getMsg();
            m_of << msg;
            m_curSize += msg.size();

            vec_char vec(new std::vector<char>(1400, 0));
            m_sock->async_read_some(buffer(*vec), bind(&FileClient::read_handle, this, boost::asio::placeholders::error, vec));
        }
    }
}

void FileClient::write_handle(const system::error_code &ec)
{
    if (ec)
    {
        return ;
    }
}

void FileClient::on_connected(const system::error_code &ec)
{
    if (ec)
    {
        return ;
    }

    m_sock->async_write_some(buffer("****"), bind(&FileClient::write_handle, this, boost::asio::placeholders::error));

    m_timer.expires_at(m_timer.expires_at() + boost::posix_time::microseconds(500));
    m_timer.async_wait(boost::bind(&FileClient::on_connected, this, boost::asio::placeholders::error));
}
