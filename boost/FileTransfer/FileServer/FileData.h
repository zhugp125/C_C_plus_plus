#ifndef FILEDATA_H
#define FILEDATA_H

#include <string>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>

#include "TcpCommon.h"

class FileData
{
public:
    enum FileType
    {
        VSERSION = 0,
        FILEINFO,
        FILE,
        CLOSE,
    };

    FileData();
    FileData(FileType type, const string text);
    FileData(FileType type, size_t length, const char* text);
    FileData(const FileData& data);

    FileType getFileType() const;
    char* data() const;
    size_t length() const;

    string dumps();
    static FileData loads(const string& str);

private:
    friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive &ar, const unsigned int)
    {
        ar & m_type;
        ar & m_data;
    }

private:
    FileType m_type;
    ByteArray m_data;
};

#endif // FILEDATA_H
