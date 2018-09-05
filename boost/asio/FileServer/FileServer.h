#ifndef FILESERVER_H
#define FILESERVER_H

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

using namespace boost;
using namespace boost::asio;

class FileServer
{
    typedef shared_ptr<ip::tcp::socket> sock_pt;
public:
    FileServer(io_service &io);

protected:
    void start();
    void accept_handle(const system::error_code &ec);
    void write_handle(const system::error_code &ec);
    void read_handle(const system::error_code &ec);

private:
    io_service &m_ios;
    ip::tcp::acceptor m_acceptor;
    sock_pt m_sock;
    std::string m_fileName;
};

#endif // FILESERVER_H
