/*************************************************************************
	> File Name: unused.cpp
	> Author: 
	> Mail: 
	> Created Time: 日  5/27 16:26:55 2018
 ************************************************************************/

//g++ unused.cpp -I/usr/local/include

#include<iostream>
#include<boost/core/ignore_unused.hpp>

using namespace std;
using namespace boost;

int func(int x, int y)
{
    int i;
    ignore_unused(x, i);

    return y;
}

int main()
{
    return 0;
}
