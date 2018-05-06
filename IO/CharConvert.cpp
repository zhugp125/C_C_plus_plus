/*************************************************************************
	> Author: zhugaopeng
	> Mail: zhugp125@sina.com
	> Created Time: 日  5/ 6 10:57:13 2018
 ************************************************************************/

#include <iostream>
#include <locale>
using namespace std;

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

int main()
{
    std::string str("中国");
    std::wcout << sToWs(str) << std::endl;
    
    std::wstring wstr(L"你好");
    std::cout << wsToS(wstr) << std::endl;

    return 0;
}
