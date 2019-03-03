#include <iostream>
#include "TcpServer.h"

#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>

int main()
{
    try
    {
        using boost::property_tree::ptree;
        ptree pt;
        read_ini("config.ini", pt);

        string strIp;
        unsigned short uPort;
        {
            ptree pt_child = pt.get_child("address");
            strIp = pt_child.get<string>("ip", "127.0.0.1");
            uPort = pt_child.get<unsigned short>("port", 8888);
        }

        io_service service;
        ip::tcp::endpoint ep(ip::tcp::v4(), uPort);
        TcpServerPtr server(make_shared<TcpServer>(service, ep));
        {
            ptree pt_child = pt.get_child("update");
            server->setVsersion(pt_child.get<string>("version", ""));
            bool bRet = server->setFileInfo(pt_child.get<string>("file", ""));
            if (!bRet)
            {
                cout << "set file info failed" << endl;
                return -1;
            }
        }
        server->start();
        service.run();
    }
    catch(const std::exception& e)
    {
        cout << "error : " << e.what() << endl;
    }

    cout << "Hello World!" << endl;
    return 0;
}
