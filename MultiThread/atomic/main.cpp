#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>

using namespace std;

#define N 100000
#define ThreadNum 10

#if 1
atomic_long g_count(0);
void func()
{
    for (int i = 0; i != N; ++i)
    {
        ++g_count;
    }
}
#else
long g_count = 0;
mutex g_mu;
void func()
{
    for (int i = 0; i != N; ++i)
    {
        lock_guard<mutex> lock(g_mu);
        ++g_count;
    }
}
#endif



int main()
{
    clock_t start = clock();

    vector<thread> threads;
    for (int i = 0; i < ThreadNum; ++i)
        threads.push_back(thread(func));

    for (int i = 0; i < ThreadNum; ++i)
        threads[i].join();

    clock_t last = clock();
    cout << "count: " << g_count << " use time: " << (last - start) << endl;

    cout << "Hello World!" << endl;
    return 0;
}
