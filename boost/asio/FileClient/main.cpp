#include <iostream>
#include "FileClient.h"

using namespace std;

int main()
{
    try
    {
        cout << "client start." << endl;
        io_service ios;

        FileClient client(ios);
        ios.run();
    }
    catch (std::exception &e)
    {
        cout << e.what() << endl;
    }

    cout << "Hello World!" << endl;
    return 0;
}
