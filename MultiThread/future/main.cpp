#include <iostream>
#include <future>

using namespace std;

int factorial(int n)
{
    int result = 1;
    for (int i = 1; i <= n; ++i)
        result *= i;

    return result;
}

int factorial1(std::future<int>& f)
{
    int n = f.get();
    int result = 1;
    for (int i = 1; i <= n; ++i)
        result *= i;

    return result;
}

int factorial2(std::shared_future<int> f)
{
    int n = f.get();
    int result = 1;
    for (int i = 1; i <= n; ++i)
        result *= i;

    return result;
}

int main()
{
    {
        // 子线程向父线程通信
        std::future<int> fu = std::async(std::launch::async, factorial, 4);
        cout << "return value: " << fu.get() << endl;
    }

    {
        // 父线程向子线程通信
        std::promise<int> p;
        std::future<int> f = p.get_future();
        std::future<int> fu = std::async(std::launch::async, factorial1, std::ref(f));
        p.set_value(4);
        cout << "return value1: " << fu.get() << endl;
    }

    {
        std::promise<int> p;
        std::future<int> f = p.get_future();
        std::shared_future<int> sf = f.share();
        std::future<int> fu = std::async(std::launch::async, factorial2, sf);
        p.set_value(4);
        cout << "return value2: " << fu.get() << endl;
    }

    cout << "Hello World!" << endl;
    return 0;
}
