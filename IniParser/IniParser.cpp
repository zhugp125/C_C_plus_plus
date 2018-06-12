#include "IniParser.h"
#include "TrimString.h"
#include <fstream>
#include <iostream>

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

bool IniParser::remove(const std::string &section)
{
    auto it = m_data.find(section);
    if (it != m_data.end())
    {
        m_data.erase(it);
        return true;
    }
    return false;
}

bool IniParser::remove(const std::string &section, const std::string &key)
{
    using namespace std;
    auto it = m_data.find(section);
    if (it != m_data.end())
    {
        auto &data = it->second;
        auto mapIt = data.find(key);
        if (mapIt != data.end())
        {
            data.erase(mapIt);
            return true;
        }
    }
    return false;
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

    FILE* f = fopen(file.c_str(), "r");
    if (NULL == f)
    {
        return false;
    }

    fseek(f, 0L, SEEK_END);
    long size = ftell(f);
    fseek(f, 0L, SEEK_SET);

    char* ch = (char *)malloc(size + 1);
    int ret = fread(ch, 1, size + 1, f);

    fclose(f);

    str = std::move(ch);

    free(ch);
    return ret >= 0;
}

bool writeFile(const std::string &file, std::string &str)
{
    if (file.empty())
    {
        return false;
    }

    FILE* f = fopen(file.c_str(), "w");
    if (NULL == f)
    {
        return false;
    }

    int ret = fwrite(str.c_str(), 1, str.size(), f);
    fclose(f);
    return ret >= 0;
}
