#ifndef FILECLIENT_H
#define FILECLIENT_H

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>

using namespace boost;
using namespace boost::asio;

class FileClient
{
    typedef shared_ptr<ip::tcp::socket> sock_pt;
    typedef shared_ptr<std::vector<char> > vec_char;
public:
    FileClient(io_service &ios);

protected:
    void start();
    void conn_handle(const system::error_code &ec);
    void read_handle(const system::error_code &ec, vec_char str);
    void write_handle(const system::error_code &ec);

private:
    io_service &m_ios;
    ip::tcp::endpoint m_ep;
    sock_pt m_sock;
};

#endif // FILECLIENT_H
