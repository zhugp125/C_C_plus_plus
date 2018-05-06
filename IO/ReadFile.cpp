/**
 * Author: zhugaopeng
 * Email : zhugp125@sina.com
 * Date  : 2018-05-05
*/

#include <iostream>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <cstdio>

std::string readFile1(const std::string& filename)
{
    std::ifstream f(filename);
    return std::string((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
}

std::string readFile2(const std::string& filename)
{
    std::ifstream f(filename);
    std::ostringstream ss;
    ss << f.rdbuf();

    return ss.str();
}

char* readFile3(const char* filename)
{
    if (NULL == filename)
    {
        return NULL;
    }

    FILE* file = fopen(filename, "r");
    if (NULL == file)
    {
        return NULL;
    }

    fseek(file, 0L, SEEK_END);
    int size = ftell(file);
    fseek(file, 0L, SEEK_SET);

    char* ch = (char*)malloc(size + 1);
    fread(ch, 1, size + 1, file);

    fclose(file);

    return ch;
}

int main()
{
    std::string filename("test.txt");

    std::cout << readFile1(filename) << std::endl;
    std::cout << readFile2(filename) << std::endl;
    char* str = readFile3(filename.c_str());
    if (NULL != str)
    {
        printf("%s\n", str);
        free(str);
    }

    return 0;
}
