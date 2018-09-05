#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <string>

enum MsgType
{
    MT_Header = 0,
    MT_File = 1
};

namespace Json
{
    class Value;
}

class MessageInfo
{
public:
    MessageInfo(const std::string &str = "");
    virtual ~MessageInfo();

    bool isHeader();
    std::string getFileName();
    std::string getFileMd5();
    std::string getMsg();
    uint16_t getFileSize();

    template<typename Key, typename Value>
    void insert(const Key &key, const Value &value);
    std::string toString();

private:
    MsgType m_type;
    std::string m_fileName;
    std::string m_fileMd5;
    uint16_t m_fileSize;
    std::string m_msg;

    Json::Value *m_write;
};

std::string readFile(const std::string &fileName);
std::string getFileMd5(const std::string &fileName);

std::string getFileName(const std::string &fileName);
long long getFileSize(const std::string &fileName);

#endif
