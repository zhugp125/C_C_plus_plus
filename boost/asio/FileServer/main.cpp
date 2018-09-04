#include <iostream>
#include "FileServer.h"

using namespace std;

int main()
{
    try
    {
        std::cout << "server start." << std::endl;
        io_service ios;

        FileServer server(ios);
        ios.run();
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    cout << "Hello World!" << endl;
    return 0;
}
