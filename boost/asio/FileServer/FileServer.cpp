#include "FileServer.h"
#include <boost/bind.hpp>
#include <iostream>
#include "../common/common.h"

FileServer::FileServer(io_service &io)
    : m_ios(io)
    , m_acceptor(m_ios, ip::tcp::endpoint(ip::tcp::v4(), 6688))
    , m_sock(new ip::tcp::socket(m_ios))
{
    boost::asio::socket_base::keep_alive keep_alive(true);
    m_sock->set_option(keep_alive);

    m_fileName = "/Users/a123/Downloads/share/library/Qt/qtftp-master.zip";
    start();
}

void FileServer::start()
{
    m_acceptor.async_accept(*m_sock, bind(&FileServer::accept_handle, this, placeholders::error));
}

void FileServer::accept_handle(const system::error_code &ec)
{
    if (ec)
    {
        return ;
    }

    std::cout << "client address: ";
    std::cout << m_sock->remote_endpoint().address().to_string() << std::endl;

    MessageInfo info;
    info.insert("type", MT_Header);
    info.insert("file", getFileName(m_fileName));
    info.insert("md5", getFileMd5(m_fileName));
    info.insert("size", getFileSize(m_fileName));

    m_sock->async_write_some(buffer(info.toString()), bind(&FileServer::write_handle, this, placeholdes::error));
    start();
}

void FileServer::write_handle(const system::error_code &ec)
{
    std::cout << "send msg complete..." << std::endl;

    shared_ptr<std::vector<char> > str(new std::vector<char>(100, 0));
    m_sock->async_read_some(buffer(*str), bind(&FileServer::read_handle, this, boost::asio::placeholders::error));
}

void FileServer::read_handle(const system::error_code &ec)
{
    //send file
}
