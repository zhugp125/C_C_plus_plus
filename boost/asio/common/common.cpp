#include "common.h"
#include "md5/md5.h"
#include "jsoncpp/json/json.h"
#include <fstream>
#include <boost/filesystem.hpp>

std::string readFile(const std::string &fileName)
{
    std::ifstream f(fileName);
    return std::string((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
}

std::string getFileMd5(const std::string &fileName)
{
    MD5 md5(readFile(fileName));
    return md5.md5();
}

MessageInfo::MessageInfo(const std::string &str)
    : m_type(MT_Header)
    , m_fileSize(0)
    , m_write(NULL)
{
    Json::Reader reader;
    Json::Value root;
    if (reader.parse(str, root))
    {
        if (root.isMember("type"))
        {
            m_type = (MsgType)(root["type"].asInt());
        }

        if (root.isMember("file"))
        {
            m_fileName = root["file"].asString();
        }

        if (root.isMember("md5"))
        {
            m_fileMd5 = root["md5"].asString();
        }

        if (root.isMember("msg"))
        {
            m_msg = root["msg"].asString();
        }

        if (root.isMember("size"))
        {
            m_fileSize = root["size"].asInt();
        }
    }
}

MessageInfo::~MessageInfo()
{
    if (NULL != m_write)
    {
        delete m_write;
        m_write = NULL;
    }
}

bool MessageInfo::isHeader()
{
    return m_type == MT_Header;
}

std::string MessageInfo::getFileName()
{
    return m_fileName;
}

std::string MessageInfo::getFileMd5()
{
    return m_fileMd5;
}

std::string MessageInfo::getMsg()
{
    return m_msg;
}

uint16_t MessageInfo::getFileSize()
{
    return m_fileSize;
}

std::string MessageInfo::toString()
{
    if (m_write != NULL)
    {
        m_write->asString();
    }
    return "";
}

template<typename Key, typename Value>
void MessageInfo::insert(const Key &key, const Value &value)
{
    if (NULL == m_write)
    {
        m_write = new Json::Value;
    }
    m_write[key] = value;
}

std::string getFileName(const std::string &fileName)
{
    boost::filesystem::path path(fileName);
    return path.filename().string();
}

long long getFileSize(const std::string &fileName)
{
    boost::filesystem::path path(fileName);
    return boost::filesystem::file_size(path);
}
