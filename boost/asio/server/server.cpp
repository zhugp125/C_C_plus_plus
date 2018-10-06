#include "server.h"

server::server(io_service& service, ip::tcp::endpoint ep)
    :m_service(service)
    ,m_acceptor(service, ep)
{
    socket_base::keep_alive keepAlive(true);
    m_acceptor.set_option(keepAlive);

    addConnect();
}

void server::addConnect()
{
    session_ptr new_session(new session(m_service));
    m_acceptor.async_accept(new_session->getSocket(), std::bind(&server::connect_handle, this, std::placeholders::_1, new_session));
}

void server::connect_handle(const boost::system::error_code &err, const session_ptr &new_session)
{
    if (!err)
    {
        cout << "connect, address: " << new_session->getSocket().remote_endpoint().address().to_string() << endl;
        new_session->start();
        addConnect();
    }
}
