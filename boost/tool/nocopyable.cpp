/*************************************************************************
	> File Name: nocopyable.cpp
	> Author: 朱高鹏
	> Mail: zhugp125@sina.com
	> Created Time: 日  5/27 16:15:00 2018
 ************************************************************************/

// g++ nocopyable.cpp -I/usr/local/include

#include<iostream>
#include<boost/noncopyable.hpp>

using namespace std;
using namespace boost;

class UniqueObject : public boost::noncopyable
{
public:
    UniqueObject(int value = 0) :m_value(value) {}

private:
    int m_value;
};

int main()
{
    UniqueObject u1(10);
    UniqueObject u2(u1); //error
    UniqueObject u3;
    u3 = u1;             //error

    return 0;
}
