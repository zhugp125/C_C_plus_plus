#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>

class Logger final
{
public:
    ~Logger() {}

    static Logger* getInstance()
    {
        static Logger log;
        return &log;
    }

    void writeInfoMsg(const std::string& info)
    {
        std::cout << "info message: " << info << std::endl;
    }
    void writeWarnMsg(const std::string& warn)
    {
        std::cout << "warn message: " << warn << std::endl;
    }
    void writeErrorMsg(const std::string& error)
    {
        std::cout << "error message: " << error << std::endl;
    }

private:
    Logger() = default;
};

#endif // LOGGER_HPP
