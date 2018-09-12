#include "FileServer.h"
#include <boost/bind.hpp>
#include <iostream>
#include <fstream>
#include "../common/common.h"

#define BUF_SIZE 200

FileServer::FileServer(io_service &io)
    : m_ios(io)
    , m_acceptor(m_ios, ip::tcp::endpoint(ip::tcp::v4(), 59000))
{
    boost::asio::socket_base::keep_alive keep_alive(true);
    boost::system::error_code ec;
    m_acceptor.set_option(keep_alive, ec);

    m_fileName = "/Users/a123/Downloads/share/library/Qt/qtftp-master.zip";
    start();
}

void FileServer::start()
{
    sock_pt sock(new boost::asio::ip::tcp::socket(m_ios));
    m_acceptor.async_accept(*sock, bind(&FileServer::accept_handle, this, boost::placeholders::_1, sock));
}

void FileServer::accept_handle(const system::error_code &ec, sock_pt sock)
{
    if (ec || (NULL == sock))
    {
        return ;
    }

    std::cout << "client address: ";
    std::cout << sock->remote_endpoint().address().to_string() << std::endl;

    MessageInfo info;
    info.insert(g_type, MT_Header);
    info.insert(g_file, getFileName(m_fileName));
    info.insert(g_md5, getFileMd5(m_fileName));
    info.insert(g_size, getFileSize(m_fileName));
    std::cout << info.toString() << std::endl;
    sock->async_write_some(buffer(info.toString()), boost::bind(&FileServer::write_handle, this, boost::placeholders::_1));

    shared_ptr<std::vector<char> > str(new std::vector<char>(100, 0));
    sock->async_read_some(buffer(*str), boost::bind(&FileServer::read_handle, this, boost::placeholders::_1, str, sock));
    start();
}

void FileServer::write_handle(const system::error_code &ec)
{
    if (ec)
    {
        return;
    }
    std::cout << "send msg complete..." << std::endl;
}

void FileServer::read_handle(const system::error_code &ec, vec_char pstr, sock_pt sock)
{
    if (ec || (NULL == sock))
    {
        return;
    }

    std::string str(pstr->begin(), pstr->end());
    //std::cout << str << std::endl;

    if (str.compare(g_begin))
    {
        std::cout << "send file" << std::endl;
        std::ifstream f(m_fileName);
        int ret = 0;
        do
        {
            char buf[BUF_SIZE] = {0};
            f.read(buf, BUF_SIZE);
            //std::cout << buf << std::endl;
            ret = sizeof(buf);
            std::cout << ret << std::endl;
            if (ret == 0)
            {
                break;
            }

            MessageInfo info;
            info.insert(g_type, MT_File);
            info.insert(g_text, std::string(buf));
            sock->async_write_some(buffer(info.toString()), boost::bind(&FileServer::write_handle, this, boost::placeholders::_1));
        }while(ret > 0);

        sock->async_write_some(buffer(g_end), boost::bind(&FileServer::write_handle, this, boost::placeholders::_1));
    }

}
