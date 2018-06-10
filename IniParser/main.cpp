#include <iostream>
#include "IniParser.h"

using namespace std;

int main()
{
    IniParser parser("config.ini");

    parser.beginGroup("login");
    parser.setValue("user", "zhugp");
    parser.setValue("password", "123456");
    parser.endGroup();

    parser.beginGroup("server");
    parser.setValue("ip", "127.0.0.1");
    parser.setValue("port", "8001");
    parser.endGroup();

    parser.setValue("max_allowed", "1024");
    parser.setValue("download", "1024k");

    parser.save();

    cout << parser.getValue("user", "no user") << endl;
    cout << parser.getValue("login", "user", "no user") << endl;

    parser.remove("server");
    parser.remove("login", "password");
    parser.save();

    cout << "Hello World!" << endl;
    return 0;
}
