#ifndef TRIMSTRING_H
#define TRIMSTRING_H

#include <string>
#include <regex>
#include <fstream>

// 去除字符串左侧的空字符
std::string trimleft(const std::string &str)
{
    std::string::size_type pos = str.find_first_not_of(" ");
    if (pos == str.npos)
    {
        return "";
    }
    return str.substr(pos);
}

// 去除字符串右侧的空字符
std::string trimright(const std::string &str)
{
    std::string::size_type pos = str.find_last_not_of(" ");
    if (pos == str.npos)
    {
        return "";
    }
    return str.substr(0, pos + 1);
}

// 去除字符串两侧的空字符
std::string trim(const std::string &str)
{
    typedef std::string::size_type size_type;

    size_type left = str.find_first_not_of(" ");
    if (left == str.npos)
    {
        return "";
    }

    size_type right = str.find_last_not_of(" ");
    if (right == str.npos)
    {
        return "";
    }
    return str.substr(left, right - left + 1);
}

// 获取section
bool parserSection(const std::string &str, std::string &section)
{
    using namespace std;

    string::size_type first = str.find_first_of("[");
    if (first == str.npos)
    {
        return false;
    }

    string::size_type second = str.find_first_of("]", first);
    if (second == str.npos)
    {
        return false;
    }

    if (first < second)
    {
        section = str.substr(first + 1, second - first - 1);
        return true;
    }
    return false;
}

bool isComment(const std::string &str)
{
    return str.empty() ? false : (str[0] == ';' || str[0] == '#');
}

bool parserKeyValue(const std::string &str, std::string &key, std::string &value)
{
    using namespace std;
    if (isComment(str))
    {
        return false;
    }

    string::size_type pos = str.find_first_of("=");
    if (pos == str.npos)
    {
        return false;
    }


    key = trim(str.substr(0, pos));
    value = trim(str.substr(pos + 1));
    return true;
}

#endif // TRIMSTRING_H
