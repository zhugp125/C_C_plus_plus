#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <string>
#include "jsoncpp/json/json.h"

enum MsgType
{
    MT_NONE = -1,
    MT_Header = 0,
    MT_File = 1
};

const std::string g_type = "type";
const std::string g_file = "file";
const std::string g_size = "size";
const std::string g_md5  = "md5";
const std::string g_text = "text";

class MessageInfo
{
public:
    MessageInfo(const std::string &str = "");
    virtual ~MessageInfo();

    MsgType getHeader();
    std::string getFileName();
    std::string getFileMd5();
    std::string getMsg();
    uint16_t getFileSize();

    template<typename Value>
    void insert(const std::string &key, const Value &value);

    std::string toString() const;

private:
    Json::Value m_root;
};

template<typename Value>
void MessageInfo::insert(const std::string &key, const Value &value)
{
    m_root[key] = Json::Value(value);
}

std::string readFile(const std::string &fileName);
std::string getFileMd5(const std::string &fileName);

std::string getFileName(const std::string &fileName);
long long getFileSize(const std::string &fileName);

void readFileBySize(const std::string &fileName);

#endif
