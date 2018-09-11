#ifndef FILESERVER_H
#define FILESERVER_H

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>

using namespace boost;
using namespace boost::asio;

class FileServer
{
    typedef shared_ptr<ip::tcp::socket> sock_pt;
    typedef shared_ptr<std::vector<char> > vec_char;
public:
    FileServer(io_service &io);

protected:
    void start();
    void accept_handle(const system::error_code &ec, sock_pt sock);
    void write_handle(const system::error_code &ec);
    void read_handle(const system::error_code &ec, vec_char str, sock_pt sock);

private:
    io_service &m_ios;
    ip::tcp::acceptor m_acceptor;
    std::string m_fileName;
};

#endif // FILESERVER_H
