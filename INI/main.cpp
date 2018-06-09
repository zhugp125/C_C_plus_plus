#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <QSettings>

using namespace std;

void save_boost(const std::string& file)
{
    using boost::property_tree::ptree;

    ptree pt;
    pt.put("login.user", "zhu");
    pt.add("login.passwprd", "123456");

    write_ini(file, pt);
}

void load_boost(const std::string& file)
{
    using boost::property_tree::ptree;

    ptree pt;
    read_ini(file, pt);

    for (auto it = pt.begin(); it != pt.end(); ++it)
    {
        cout << it->first << "\n";
        const ptree &child_pt = it->second;
        for (auto cit = child_pt.begin(); cit != child_pt.end(); ++cit)
        {
            cout << cit->first << " = " << child_pt.get<string>(cit->first) << "\n";
        }
    }
}

// 会按key进行排序
void save_qt(const QString& file)
{
    QSettings setting(file, QSettings::IniFormat);
    setting.beginGroup("login");
    setting.setValue("user", "zhu");
    setting.setValue("password", "123456");
    setting.endGroup();
}

void load_qt(const QString& file)
{
    QSettings setting(file, QSettings::IniFormat);
    setting.beginGroup("login");
    for (const QString& key: setting.allKeys())
    {
        cout << key.toStdString() << " = " << setting.value(key).toString().toStdString() << "\n";
    }
    setting.endGroup();
}

int main()
{
    //save_boost("test.ini");
    //load_boost("test.ini");

    //save_qt("test.ini");
    //load_qt("test.ini");

    cout << "Hello World!" << endl;
    return 0;
}
