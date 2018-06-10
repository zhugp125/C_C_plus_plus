#ifndef INIPARSER_H
#define INIPARSER_H

#include <map>
#include <string>

class IniParser
{
public:
    IniParser(const std::string &file = "");

    bool load(const std::string &file);
    bool save();
    bool saveAs(const std::string &file);

    std::string getValue(const std::string &key, const std::string &defaultValue = "");
    std::string getValue(const std::string &section, const std::string &key, const std::string &defaultValue);
    void setValue(const std::string &key, const std::string &value);
    void setValue(const std::string &section, const std::string &key, const std::string &value);

    bool remove(const std::string &section);
    bool remove(const std::string &section, const std::string &key);

    void beginGroup(const std::string &section);
    void endGroup();

private:
    std::string m_file;
    std::string m_section;
    std::map<std::string, std::map<std::string, std::string> > m_data;
};

bool readFile(const std::string &file, std::string &str);
bool writeFile(const std::string &file, std::string &str);

#endif // INIPARSER_H
