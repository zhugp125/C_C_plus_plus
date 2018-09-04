#ifndef FILECLIENT_H
#define FILECLIENT_H

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>

using namespace boost;
using namespace boost::asio;

class FileClient
{
public:
    FileClient(io_service &ios);

protected:
    void start();
    void conn_handle(const system::error_code &ec, sock_pt sock);
    void read_handle(const system::error_code &ec, vec_char str);

private:
    io_service &m_ios;
    ip::tcp::endpoint m_ep;
    typedef shared_ptr<ip::tcp::socket> sock_pt;
    typedef shared_ptr<std::vector<char> > vec_char;
};

#endif // FILECLIENT_H
