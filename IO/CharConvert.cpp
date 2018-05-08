/*************************************************************************
	> Author: zhugaopeng
	> Mail: zhugp125@sina.com
	> Created Time: 日  5/ 6 10:57:13 2018
 ************************************************************************/

 #define QT
 
#include <iostream>
#include <string>
#include <locale>
#include <boost/locale.hpp>

#ifdef QT
#include <QString>
#endif

#ifdef _WIN32
#include <windows.h>
#endif

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

#ifdef QT
std::wstring sToWs_Qt(const std::string &str)
{
    return QString::fromStdString(str).toStdWString();
}

std::string wsToS_Qt(const std::wstring &wstr)
{
    return QString::fromStdWString(wstr).toStdString();
}
#endif

#ifdef _WIN32
std::wstring sTows_w(const std::string &str)
{
    int nLen = str.size();
    int nSize = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)str.c_str(), nLen, 0, 0);
    if (nSize <= 0)
        return NULL;

    WCHAR* pwch = new WCHAR[nSize + 1];
    if (NULL == pwch)
        return NULL;

    MultiByteToWideChar(CP_ACP, 0, (LPCSTR)str.c_str(), nLen, pwch, nSize);
    pwch[nSize] = 0;

    if (pwch[0] == 0xfeff)
    {
        for (int i = 0; i < nSize; ++i)
            pwch[i] = pwch[i + 1];
    }

    std::wstring wstr(pwch);
    delete[]pwch;

    return wstr;
}

std::string wsToS_w(const std::wstring &wstr)
{
    int nLen = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wstr.c_str(), -1, NULL, 0, NULL, NULL);
    if (nLen <= 0)
    {
        return "";
    }

    char* pch = new char[nLen];
    if (NULL == pch)
    {
        return "";
    }

    WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wstr.c_str(), -1, (LPSTR)pch, nLen, NULL, NULL);
    pch[nLen - 1] = 0;

    std::string str(pch);
    delete []pch;

    return str;
}

#endif

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

#ifdef QT
    std::cout << "*****************************" << std::endl;
    std::wcout << sToWs_Qt(tmp1) << std::endl;
    std::cout << wsToS_Qt(wtmp1) << std::endl;
#endif

#ifdef _WIN32
    std::wcout << sTows_w(tmp1) << std::endl;
    std::cout << wsToS_w(wtmp1) << std::endl;
#endif

    return 0;
}
