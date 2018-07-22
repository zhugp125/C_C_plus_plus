#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    //保存cout的缓冲区指针
    streambuf* coutBuf = cout.rdbuf();

    ofstream out("out.txt");
    //重定向
    cout.rdbuf(out.rdbuf());

    cout << "Name: " << "zhugp" << endl;
    cout << "Sex : " << "m" << endl;
    cout << "Age : " << "26" << endl;

    out.flush();
    out.close();

    //恢复原先的缓冲区
    cout.rdbuf(coutBuf);

    cout << "Name: " << "zhugp" << endl;
    cout << "Sex : " << "m" << endl;
    cout << "Age : " << "26" << endl;

    cout << "Hello World!" << endl;
    return 0;
}
