#include <iostream>
#include <string>
#include <thread>
#include "singleton.hpp"

using namespace std;

class Test
{
public:
    Test()
    {
        cout << "Test()" << endl;
    }

    ~Test()
    {
        cout << "~Test()" << endl;
    }

    void setName(const string& name)
    {
        m_name = name;
    }

    string getName()
    {
        return m_name;
    }

private:
    string m_name;
};

void func()
{
    Singleton<Test>::instance()->setName("zhu");
    cout << Singleton<Test>::instance()->getName() << endl;
}

int main()
{
    std::thread t(func);
    t.join();

    cout << Singleton<Test>::instance()->getName() << endl;
    cout << "hello world" << endl;
    return 0;
}
