#include "IniParser.h"
#include "TrimString.h"
#include <fstream>

IniParser::IniParser(const std::string &file)
    : m_file(file)
{
    load(file);
}

bool IniParser::saveAs(const std::string &file)
{
    using namespace std;
    string content;
    for (auto it = m_data.cbegin(); it != m_data.end(); ++it)
    {
        const string &key = it->first;
        if (!key.empty())
        {
            content.append("[");
            content.append(key);
            content.append("]\n");
        }

        const map<string, string> &data = it->second;
        for (auto secIt = data.cbegin(); secIt != data.cend(); ++secIt)
        {
            content.append(secIt->first);
            content.append("=");
            content.append(secIt->second);
            content.append("\n");
        }
        content.append("\n");
    }

    return writeFile(file, content);
}

bool IniParser::save()
{
    return saveAs(m_file);
}

bool IniParser::load(const std::string &file)
{
    using namespace std;

    string content;
    if (!readFile(file, content) || content.empty())
    {
        return false;
    }

    string::size_type first = 0, second = 0;
    string::size_type count = content.size();
    while (true)
    {
        second = content.find_first_of("\n", first);
        if (second > count)
        {
            break;
        }

        string line = content.substr(first, second - first);
        first = second + 1;
        if (line.empty() || isComment(line))
        {
            continue;
        }

        string section;
        if (parserSection(line, section))
        {
            m_section = std::move(section);
        }
        else
        {
            string key, value;
            if (parserKeyValue(line, key, value))
            {
                m_data[m_section][key] = value;
            }
        }
    }
    return true;
}

std::string IniParser::getValue(const std::string &key, const std::string &defaultValue)
{
    return getValue(m_section, key, defaultValue);
}

std::string IniParser::getValue(const std::string &section, const std::string &key, const std::string &defaultValue)
{
    using namespace std;
    map<string, string> &data = m_data[section];
    if (data.find(key) == data.end())
    {
        return defaultValue;
    }
    return data[key];
}

void IniParser::setValue(const std::string &key, const std::string &value)
{
    setValue(m_section, key, value);
}

void IniParser::setValue(const std::string &section, const std::string &key, const std::string &value)
{
    m_data[section][key] = value;
}

void IniParser::beginGroup(const std::string &section)
{
    m_section = section;
}

void IniParser::endGroup()
{
    m_section.clear();
}

bool readFile(const std::string &file, std::string &str)
{
    if (file.empty())
    {
        return false;
    }

    std::ifstream f(file);
    bool ok = f.is_open();
    if (ok)
    {
        str = std::string((std::istreambuf_iterator<char>(f)),
                           std::istreambuf_iterator<char>());
    }

    return ok;
}

bool writeFile(const std::string &file, std::string &str)
{
    if (file.empty())
    {
        return false;
    }

    std::ofstream f(file);
    bool ok = f.is_open();
    if (ok)
    {
        f << str;
    }
    return ok;
}
