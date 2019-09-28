#include "StandardOutputLogger.h"
#include <iostream>

StandardOutputLogger::StandardOutputLogger()
{

}

void StandardOutputLogger::writeInfoMsg(const std::string &info)
{
    std::cout << "info message: " << info << std::endl;
}

void StandardOutputLogger::writeWarnMsg(const std::string &warn)
{
    std::cout << "warn message: " << warn << std::endl;
}

void StandardOutputLogger::writeErrorMsg(const std::string &error)
{
    std::cout << "error message: " << error << std::endl;
}
