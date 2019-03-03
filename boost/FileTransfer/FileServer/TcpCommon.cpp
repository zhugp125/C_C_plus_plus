#include "TcpCommon.h"
#include <md5.h>
#include <boost/filesystem.hpp>

constexpr int READ_FILE_SIZE = 64 * 1024;

void charToByte(ByteArray &data, const char *text, const size_t len)
{
    data.resize(len);
    memcpy(&data[0], text, len);
}

void byteToChar(char *text, size_t &len, const ByteArray &data)
{
    len = data.size();
    memcpy(text, &data[0], len);
}

string getFileMd5(const string &fileName)
{
    FILE* fp = fopen(fileName.c_str(), "rb");
    if (nullptr == fp)
    {
        return "";
    }

    MD5 md5;
    char buf[READ_FILE_SIZE];
    while (!feof(fp))
    {
        size_t len = fread(buf, 1, READ_FILE_SIZE, fp);
        md5.update(buf, len);
    }
    md5.finalize();
    return md5.md5();
}

size_t getFileSize(const string &fileName)
{
    using namespace boost::filesystem;
    return file_size(path(fileName));
}

string getFileName(const string &fileName)
{
    using namespace boost::filesystem;
    return basename(path(fileName));
}
