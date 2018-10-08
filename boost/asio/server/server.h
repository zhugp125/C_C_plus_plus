#ifndef SERVER_H
#define SERVER_H

#include "session.h"

class server
{
public:
    server(io_service& service, ip::tcp::endpoint ep);

private:
    void addConnect();
    void connect_handle(const boost::system::error_code& err, const session_ptr& new_session);

private:
    io_service& m_service;
    ip::tcp::acceptor m_acceptor;
};

#endif // SERVER_H
