#include <iostream>
using namespace std;

enum LoggerType
{
    INFO = 0,
    ERROR,
    DEBUG
};

class Logger
{
public:
    Logger(int level) : m_nextLogger(nullptr), m_level(level) {}
    virtual ~Logger() {}

    void setNextLogger(Logger* nextLogger) { m_nextLogger = nextLogger; }

    void logMessage(int level, const string& msg)
    {
        if (m_level <= level)
        {
            write(msg);
        }
        if (m_nextLogger != nullptr)
        {
            m_nextLogger->logMessage(level, msg);
        }
    }

protected:
    virtual void write(const string& msg) = 0;

private:
    Logger* m_nextLogger;
    int m_level;
};

class InfoLogger : public Logger
{
public:
    InfoLogger(int level) : Logger(level) {}

protected:
    void write(const string &msg)
    {
        cout << "InfoLogger " << msg << endl;
    }
};

class ErrorLogger : public Logger
{
public:
    ErrorLogger(int level) : Logger(level) {}

protected:
    void write(const string &msg)
    {
        cout << "ErrorLogger " << msg << endl;
    }
};

class DebugLogger : public Logger
{
public:
    DebugLogger(int level) : Logger(level) {}

protected:
    void write(const string &msg)
    {
        cout << "DebugLogger " << msg << endl;
    }
};

int main()
{
    Logger* debug = new DebugLogger(DEBUG);
    Logger* error = new ErrorLogger(ERROR);
    Logger* info = new InfoLogger(INFO);

    debug->setNextLogger(error);
    error->setNextLogger(info);

    debug->logMessage(DEBUG, "debug message");
    cout << endl;
    debug->logMessage(ERROR, "error message");
    cout << endl;
    debug->logMessage(INFO, "info message");
    cout << endl;

    delete debug;
    delete error;
    delete info;

    cout << "Hello World!" << endl;
    return 0;
}
