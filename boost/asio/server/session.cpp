#include "session.h"

session::session(io_service &service)
    :m_socket(new ip::tcp::socket(service))
    ,m_readMsg{0}
{

}

session::~session()
{
    close();
}

ip::tcp::socket& session::getSocket()
{
    return *m_socket;
}

void session::start()
{
    memset(m_readMsg, 0, strlen(m_readMsg));
    m_socket->async_read_some(buffer(m_readMsg, BUF_SIZE), std::bind(&session::read_handle, shared_from_this(), std::placeholders::_1));
}

void session::close()
{
    m_socket->close();
}

void session::sendData(const string &msg)
{
    m_socket->async_write_some(buffer(msg), std::bind(&session::write_handle, shared_from_this(), std::placeholders::_1));
}

void session::read_handle(const boost::system::error_code &err)
{
    if (!err)
    {
        cout << "from client size: " << strlen(m_readMsg) << " data: " << m_readMsg << endl;
        start();

        sendData(m_readMsg);
    }
    else
    {
        std::cout << "read handle: " << err.message() << std::endl;
        close();
    }
}

void session::write_handle(const boost::system::error_code &err)
{
    if (!err)
    {
        //cout << "on data send" << endl;
    }
    else
    {
        std::cout << "write handle: " << err.message() << std::endl;
        close();
    }
}
