#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "TcpSession.h"
#include <list>
#include <mutex>

class TcpServer : public std::enable_shared_from_this<TcpServer>
{
public:
    TcpServer(io_service& service, ip::tcp::endpoint ep);
    virtual ~TcpServer();

    void start();
    void remove(const TcpSessionPtr& session);
    size_t getConnectNum() const;

    string getVersion() const;
    void setVsersion(const string& strVersion);

    string getFileInfo() const;
    bool setFileInfo(const string& strFileName);

    void notify(const FileDataPtr& pFileData, const TcpSessionPtr& pTcpSession);

private:
    void connectHandle(const std::error_code& err, const TcpSessionPtr& session);

    bool readFile(char *buf, const size_t& offset, const size_t& bufSize, size_t& readSize);

private:
    io_service& m_service;
    ip::tcp::acceptor m_acceptor;

    list<TcpSessionPtr> m_tcpSessions;

    mutable mutex m_mutex;
    FilePtr m_pFile;

    string m_strVersion;
    string m_strFileInfo;
};

#endif // TCPSERVER_H
