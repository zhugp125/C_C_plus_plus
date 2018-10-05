#include "client.h"
#include <iostream>
#include <functional>
#include <thread>
#include <vector>
#include <boost/bind.hpp>

typedef vector<char> ByteArray;

client::client(io_service &service, ip::tcp::endpoint ep)
    :m_service(service)
    ,m_socket(new ip::tcp::socket(service))
    ,m_readMsg{0}
{
    m_socket->async_connect(ep, std::bind(&client::connect_handle, this, std::placeholders::_1));
}

client::~client()
{

}

void client::sendData(const string &msg)
{
    do_sendData(msg);
    //m_service.post(std::bind(&client::do_sendData, this, msg));
}

void client::close()
{
    do_close();
    //m_service.post(std::bind(&client::do_close, this));
}

void client::connect_handle(const boost::system::error_code &err)
{
    if (!err)
    {
        cout << "connect, address: " << m_socket->remote_endpoint().address().to_string() << endl;
        recvData();
    }
    else
    {
        do_close();
    }
}

void client::write_handle(const boost::system::error_code &err)
{
    if (!err)
    {
        //cout << "send data ok" << endl;
    }
    else
    {
        do_close();
    }
}

void client::read_handle(const boost::system::error_code &err)
{
    if (!err)
    {
        cout << "from server size: " << strlen(m_readMsg) << " data: " << m_readMsg << endl;
        recvData();
    }
    else
    {
        do_close();
    }
}

void client::do_sendData(const string &msg)
{
    m_socket->async_write_some(buffer(msg), std::bind(&client::write_handle, this, std::placeholders::_1));
}

void client::do_close()
{
    m_service.stop();
    m_socket->close();
}

void client::recvData()
{
    memset(m_readMsg, 0, strlen(m_readMsg));
    m_socket->async_read_some(buffer(m_readMsg, BUF_SIZE), std::bind(&client::read_handle, this, std::placeholders::_1));
}
