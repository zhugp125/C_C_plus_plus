#include <iostream>
#include "server.h"

int main()
{
    try
    {
        typedef shared_ptr<server> ServerPtr;

        io_service service;
        ip::tcp::endpoint ep(ip::tcp::v4(), 8888);
        ServerPtr s(new server(service, ep));

        service.run();
    }
    catch(const std::exception& e)
    {
        cout << e.what() << endl;
    }
    cout << "Hello world" << endl;
    return 0;
}
