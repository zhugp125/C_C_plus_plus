#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "logger.hpp"

class Client
{
public:
    Client() {}
    ~Client() {}

    bool login()
    {
        Logger::getInstance()->writeInfoMsg("login successfully");
        return true;
    }

    bool logout()
    {
        Logger::getInstance()->writeInfoMsg("logout successfully");
        return true;
    }

    void searchFailed()
    {
        Logger::getInstance()->writeErrorMsg("Search Failed");
    }
};

#endif // CLIENT_HPP
