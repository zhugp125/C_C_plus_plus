#include "TcpServer.h"
#include "FileData.h"

#include <iostream>
#include <json/json.h>

constexpr int MAX_CONNECT = 2000;

constexpr int READ_FILE_SIZE = 64 * 1024;

TcpServer::TcpServer(io_service &service, ip::tcp::endpoint ep)
    : m_service(service)
    , m_acceptor(service, ep)
{
    socket_base::keep_alive keepAlive(true);
    m_acceptor.set_option(keepAlive);
}

TcpServer::~TcpServer()
{
}

void TcpServer::remove(const TcpSessionPtr &session)
{
    m_tcpSessions.remove(session);
}

size_t TcpServer::getConnectNum() const
{
    return m_tcpSessions.size();
}

string TcpServer::getVersion() const
{
    return m_strVersion;
}

void TcpServer::setVsersion(const string &strVersion)
{
    m_strVersion = strVersion;
}

string TcpServer::getFileInfo() const
{
    return m_strFileInfo;
}

bool TcpServer::setFileInfo(const string &strFileName)
{
    Json::Value root;
    root["name"] = Json::Value(getFileName(strFileName));
    root["size"] = Json::Value((uint64_t)getFileSize(strFileName));
    root["md5"] = Json::Value(getFileMd5(strFileName));

    Json::FastWriter writer;
    m_strFileInfo = writer.write(root);

    FILE* fp = fopen(strFileName.c_str(), "rb");
    if (nullptr != fp)
    {
        m_pFile = shared_ptr<FILE>(fp, ::fclose);
    }
    return nullptr != fp;
}

void TcpServer::notify(const FileDataPtr &pFileData, const TcpSessionPtr &pTcpSession)
{
    switch (pFileData->getFileType())
    {
    case FileData::VSERSION:
        {
            FileData data(FileData::VSERSION, getVersion());
            pTcpSession->sendData(data.dumps());
        }
        break;
    case FileData::FILEINFO:
        {
            FileData data(FileData::FILEINFO, getFileInfo());
            pTcpSession->sendData(data.dumps());
        }
        break;
    case FileData::FILE:
        {
            char buf[READ_FILE_SIZE] = {0};
            size_t size = 0;
            if (!readFile(buf, pTcpSession->getOffset(), READ_FILE_SIZE, size))
            {
                FileData data(FileData::CLOSE, "");
                pTcpSession->sendData(data.dumps());
            }
            else if (size > 0)
            {
                FileData data(FileData::FILE, size, buf);
                pTcpSession->sendData(data.dumps());
                pTcpSession->addOffset(size);
            }
        }
        break;
    case FileData::CLOSE:
        pTcpSession->close();
        break;
    default:
        break;
    }
}

void TcpServer::start()
{
    if (getConnectNum() < MAX_CONNECT)
    {
        TcpSessionPtr session(new TcpSession(m_service));
        session->setNotifyFunc(std::bind(&TcpServer::notify, shared_from_this(), std::placeholders::_1, session));
        SocketPtr socketPtr = session->getSocketPtr();
        m_acceptor.async_accept(*socketPtr, std::bind(&TcpServer::connectHandle, shared_from_this(), std::placeholders::_1, session));
    }
}

void TcpServer::connectHandle(const error_code &err, const TcpSessionPtr &session)
{
    cout << err.message() << endl;
    if (!err)
    {
        m_tcpSessions.push_back(session);
        session->start();
        start();
    }
    else
    {
        session->close();
    }
}

bool TcpServer::readFile(char *buf, const size_t& offset, const size_t &bufSize, size_t &readSize)
{
    bool ok = false;
    {
        lock_guard<mutex> lock(m_mutex);
        FILE* fp = m_pFile.get();
        fseek(fp, offset, SEEK_SET);

        if (!feof(fp))
        {
            readSize = fread(buf, bufSize, 1, fp);
            ok = true;
        }
    }
    return ok;
}
