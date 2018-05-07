/*************************************************************************
	> Author: zhugaopeng
	> Mail: zhugp125@sina.com
	> Created Time: 日  5/ 6 10:57:13 2018
 ************************************************************************/

#include <iostream>
#include <locale>
#include <boost/locale.hpp>
#include <QString>
using namespace std;

//comple - link
//g++ CharConvert.cpp -L/usr/local/lib -lboost_locale -I/usr/local/include

std::wstring sToWs(const std::string &str)
{
    size_t len = str.size() + 1;
    wchar_t* dest = new wchar_t[len];
    wmemset(dest, 0, len);

    mbstowcs(dest, str.c_str(), len);

    std::wstring wstr(dest);
    delete []dest;

    return wstr;
}

std::string wsToS(const std::wstring &wstr)
{
    size_t len = wstr.size() * 3 + 1;
    setlocale(LC_CTYPE, "");

    char* dest = new char[len];
    memset(dest, 0, len);

    wcstombs(dest, wstr.c_str(), len);

    std::string str(dest);
    delete []dest;

    return str;
}

std::wstring sToWs_Qt(const std::string &str)
{
    return QString::fromStdString(str).toStdWString();
}

std::string wsToS_Qt(const std::wstring &wstr)
{
    return QString::fromStdWString(wstr).toStdString();
}

int main()
{
    std::string str("中国");
    std::wcout << sToWs(str) << std::endl;

#ifdef _WIN32
    std::wcout.imbue(std::locale("chs"));
#else
    std::wcout.imbue(std::locale("zh_CN"));
#endif

    std::wstring wstr(L"你好");
    std::cout << wsToS(wstr) << std::endl;
    
    std::cout << "*****************************" << std::endl;
    std::wstring wtmp1 = L"中国，你好";
    std::string tmp1 = "中国，你好";

    std::wstring wtmp2 = boost::locale::conv::to_utf<wchar_t>(tmp1, "UTF-8");
    std::string tmp2 = boost::locale::conv::from_utf<wchar_t>(wtmp1, "UTF-8");

    std::wcout << wtmp2 << std::endl;
    std::cout << tmp2 << std::endl;

    std::cout << "*****************************" << std::endl;
    std::wcout << sToWs_Qt(tmp1) << std::endl;
    std::cout << wsToS_Qt(wtmp1) << std::endl;

    return 0;
}
