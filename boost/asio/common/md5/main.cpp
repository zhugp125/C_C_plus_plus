/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 六 11/10 14:36:41 2018
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <string.h>
#include "md5.h"
using namespace std;

#define BUFFER_SIZE  64 * 1024

bool isFile(const string& path)
{
    ifstream f(path);
    return f.is_open();
}

string getMd5(const string& path, bool isFile)
{
    MD5 md5;
    if (!isFile)
    {
        md5.update(path.c_str(), path.size());
    }
    else
    {
        ifstream f(path.c_str(), ios_base::binary);
        char buf[BUFFER_SIZE];
        while (!f.eof())
        {
            f.read(buf, sizeof(buf));
            md5.update(buf, f.gcount());
        }
    }
    md5.finalize();
    return md5.md5();
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        cout << "input error" << endl;
        return 1;
    }

    for (int i = 1; i != argc; ++i)
    {
        const string path = argv[i];
        bool bFile = isFile(path);
        cout << (bFile ? "File:" : "Str:") << "\t" << path << "\t" << getMd5(path, bFile) << endl;
    }

    return 0;
}
