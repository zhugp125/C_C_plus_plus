#include <iostream>
#include <boost/asio/ip/address.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

using namespace std;
using namespace boost::asio;

void test_addr()
{
    /**
      * static ip::address::from_string(str)
      * 参数是一个ipv4地址(.隔开)，或ipv6地址(十六进制表示)
    */
    ip::address addr = ip::address::from_string("127.0.0.1");

    /**
      * ip::adress::to_string()
      * 返回这个地址的字符串
    */
    cout << "address: " << addr.to_string() << endl;

    // 解析网址的错误方法
    try
    {
        ip::address::from_string("www.baidu.com");
    }
    catch(...)
    {
        cout << "Invalid argument" << endl;
    }

    // 解析网址的正确方法
    io_service service;
    ip::tcp::resolver resolver(service);
    ip::tcp::resolver::query query("www.baidu.com", "80");
    ip::tcp::resolver::iterator iter = resolver.resolve(query);
    ip::tcp::endpoint ep = *iter;
    cout << ep.address().to_string() << endl; //61.135.169.121
}

void test_endpoint()
{
    /**
      * 默认的构造参数
      * ip::tcp::endpoint()
    */
    ip::tcp::endpoint ep1;

    /**
      *  创建可以连接新端口的服务器socket
      * ip::tcp::endpoint(protocol, port)
    */
    ip::tcp::endpoint ep2(ip::tcp::v4(), 8000);

    /**
      * 创建连接某一个地址和端点的端口
      * ip::tcp::endpoint(addr, port)
    */
    ip::tcp::endpoint ep3(ip::address::from_string("127.0.0.1"), 8000);
}

int main()
{
    test_addr();
    test_endpoint();

    cout << "Hello World!" << endl;
    return 0;
}
