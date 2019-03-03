#include "FileData.h"
#include <sstream>

FileData::FileData()
    : m_type(VSERSION)
{

}

FileData::FileData(FileData::FileType type, const string text)
    : m_type(type)
{
    charToByte(m_data, text.c_str(), text.size());
}

FileData::FileData(FileType type, size_t length, const char *text)
    : m_type(type)
{
    charToByte(m_data, text, length);
}

FileData::FileData(const FileData &data)
    : m_type(data.m_type)
    , m_data(data.m_data)
{

}

FileData::FileType FileData::getFileType() const
{
    return m_type;
}

char *FileData::data() const
{
    return (char*)&m_data[0];
}

size_t FileData::length() const
{
    return m_data.size();
}

string FileData::dumps()
{
    ostringstream ss;
    boost::archive::binary_oarchive oa(ss);
    oa << *this;

    return ss.str();
}

FileData FileData::loads(const string &str)
{
    istringstream ss(str);
    boost::archive::binary_iarchive ia(ss);

    FileData data;
    ia >> data;
    return data;
}
