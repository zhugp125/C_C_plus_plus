#ifndef LOGGERIMP_H
#define LOGGERIMP_H

#include <string>
#include <memory>

class CLoggerImp
{
public:
    CLoggerImp();
    virtual ~CLoggerImp();

    virtual void writeInfoMsg(const std::string& info) = 0;
    virtual void writeWarnMsg(const std::string& warn) = 0;
    virtual void writeErrorMsg(const std::string& error) = 0;
};

typedef std::shared_ptr<CLoggerImp> CLoggerImpPtr;



#endif // LOGGERIMP_H


