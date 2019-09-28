#ifndef STANDARDOUTPUTLOGGER_H
#define STANDARDOUTPUTLOGGER_H

#include "LoggerImp.h"

class StandardOutputLogger : public CLoggerImp
{
public:
    StandardOutputLogger();

    virtual void writeInfoMsg(const std::string& info);
    virtual void writeWarnMsg(const std::string& warn);
    virtual void writeErrorMsg(const std::string& error);
};

#endif // STANDARDOUTPUTLOGGER_H
