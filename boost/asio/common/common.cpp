#include "common.h"
#include "md5/md5.h"
#include <fstream>
#include <sstream>
#include <string>
#include <boost/filesystem.hpp>

#define BUF_SIZE 1024

MessageInfo::MessageInfo(const std::string &str)
{
    if (!str.empty())
    {
        Json::CharReaderBuilder bulider;
        Json::CharReader * reader = bulider.newCharReader();
        const char* s = str.c_str();
        std::string err;
        if (NULL != reader && reader->parse(s, s + str.size(), &m_root, &err))
        {
            std::cout << "parse success" << std::endl;
        }
    }
}

MessageInfo::~MessageInfo()
{

}

MsgType MessageInfo::getHeader()
{
    MsgType _type = MT_NONE;
    if (!m_root[g_type].isNull())
    {
        _type = (MsgType)(m_root[g_type].asInt());
    }
    return _type;
}

std::string MessageInfo::getFileName()
{
    std::string fileName;
    if (!m_root[g_file].isNull())
    {
        fileName = m_root[g_file].asString();
    }
    return fileName;
}

std::string MessageInfo::getFileMd5()
{
    std::string fileMd5;
    if (!m_root[g_md5].isNull())
    {
        fileMd5 = m_root[g_md5].asString();
    }
    return fileMd5;
}

std::string MessageInfo::getMsg()
{
    std::string text;
    if (!m_root[g_text].isNull())
    {
        text = m_root[g_text].asString();
    }
    return text;
}

uint16_t MessageInfo::getFileSize()
{
    uint16_t size = 0;
    if (!m_root[g_size].isNull())
    {
        size = m_root[g_size].asUInt64();
    }
    return size;
}

std::string MessageInfo::toString() const
{
    std::string str;
    if (m_root.isNull() || m_root.empty())
    {
        return str;
    }

    Json::StreamWriterBuilder bulider;
    Json::StreamWriter* writer = bulider.newStreamWriter();
    if (NULL != writer)
    {
        std::ostringstream os;
        writer->write(m_root, &os);
        str = os.str();
    }
    return str;
}

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

void readFileBySize(const std::string &fileName)
{
    std::ifstream f(fileName);
    size_t size = 0;
    do
    {
        char buf[BUF_SIZE] = {0};
        f.read(buf, BUF_SIZE);
        size = strlen(buf);
        std::cout << size << std::endl;
    }while(size != 0);
}
