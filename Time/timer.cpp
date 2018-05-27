/*************************************************************************
	> File Name: timer.cpp
	> Author: 朱高鹏
	> Mail: zhugp125@sina.com
	> Created Time: 日  5/27 15:44:02 2018
 ************************************************************************/
// g++ timer.hpp -I/usr/local/include

#include <iostream>
#include <boost/timer.hpp>

#define N 1000000

using namespace std;
using namespace boost;

int main()
{
    timer t;
    cout << "max elapsed time: " << t.elapsed_max() << endl;
    cout << "min elapsed time: " << t.elapsed_min() << endl;

    int ret = 0;
    for (int i = 0; i != N; ++i)
    {
        ret += i * i;
    }
    cout << "elapsed time: " << t.elapsed() << endl;

    //restart timer
    t.restart();
    ret = 0;
    cout << "restart time\n";
    for (int i = 0; i != N; ++i)
    {
        ret += i;
    }
    cout << "elapsed time: " << t.elapsed() << endl;
    
    return 0;
}
