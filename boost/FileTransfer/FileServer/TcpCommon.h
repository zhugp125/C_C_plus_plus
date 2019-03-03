#ifndef TCPCOMMON_H
#define TCPCOMMON_H

#include <vector>
#include <memory>
#include <functional>

using namespace std;

typedef vector<char> ByteArray;
typedef shared_ptr<FILE> FilePtr;

class TcpConnection;
typedef shared_ptr<TcpConnection> TcpConnectionPtr;

class TcpSession;
typedef shared_ptr<TcpSession> TcpSessionPtr;

class TcpServer;
typedef shared_ptr<TcpServer> TcpServerPtr;

class FileData;
typedef shared_ptr<FileData> FileDataPtr;

typedef function<void(const FileDataPtr &)> NotifyFunc;

void charToByte(ByteArray& array, const char* text, const size_t len);
void byteToChar(char* text, size_t& len, const ByteArray &array);

string getFileMd5(const string& fileName);
size_t getFileSize(const string& fileName);
string getFileName(const string& fileName);

#endif // TCPCOMMON_H
