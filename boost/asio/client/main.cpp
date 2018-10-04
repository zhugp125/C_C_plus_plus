#include <iostream>
#include <memory>
#include <functional>
#include <vector>
#include <thread>
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>

using namespace std;
using namespace boost::asio;

io_service g_service;
ip::tcp::endpoint g_endpoint(ip::address::from_string("127.0.0.1"), 8888);

typedef vector<char> ByteArray;
typedef shared_ptr<ip::tcp::socket> socket_ptr;
socket_ptr g_pSock(new ip::tcp::socket(g_service));

const size_t BUF_SIZE = 1024;

void recvData();

void write_handle(const boost::system::error_code& err)
{
    if (!err)
    {
        cout << "on data send" << endl;
    }
}

void sendData(const string& msg)
{
    ByteArray data;
    data.resize(msg.size());
    memcpy(&data[0], msg.c_str(), msg.size());

    g_pSock->async_write_some(buffer(data, data.size()), std::bind(&write_handle, std::placeholders::_1));
}

void read_handle(const boost::system::error_code& err, const char* data)
{
    if (!err)
    {
        cout << "from server size: " << strlen(data) << " data: " << data << endl;
        g_service.post(std::bind(&recvData));
    }
}

void recvData()
{
    char data[BUF_SIZE] = {0};
    g_pSock->async_read_some(buffer(data, BUF_SIZE), std::bind(&read_handle, std::placeholders::_1, data));
}

void connect_handle(const boost::system::error_code& err)
{
    if (!err)
    {
        cout << "connect, address: " << g_pSock->remote_endpoint().address().to_string() << endl;
        //recvData();
    }
}

void sendDataFromCmd()
{
    string line;
    while(getline(cin, line))
    {
        sendData(line);
        if (line == "q")
        {
            break;
        }
    }
}

int main()
{
    try
    {
        g_pSock->async_connect(g_endpoint, std::bind(&connect_handle, std::placeholders::_1));

        g_service.run();
        thread(sendDataFromCmd).join();

        g_pSock->close();
    }
    catch(const std::exception& e)
    {
        cout << e.what() << endl;
    }
    cout << "Hello world" << endl;
    return 0;
}
