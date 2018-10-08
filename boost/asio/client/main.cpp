#include <iostream>
#include <boost/bind.hpp>
#include <thread>
#include "client.h"

using namespace std;

int main()
{
    try
    {
        typedef shared_ptr<client> ClientPtr;

        io_service service;
        ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 8888);
        ClientPtr c(new client(service, ep));

        thread t(boost::bind(&boost::asio::io_service::run, &service));

        string line;
        while(getline(cin, line))
        {
            c->sendData(line);
        }

        c->close();
        t.join();
    }
    catch(const std::exception& e)
    {
        cout << e.what() << endl;
    }
    cout << "Hello world" << endl;
    return 0;
}
