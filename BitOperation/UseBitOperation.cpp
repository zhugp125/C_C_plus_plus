/*************************************************************************
	> File Name: UseBitOperation.cpp
	> Author: 朱高鹏
	> Mail: zhugp125@sina.com
	> Created Time: 六  5/26 16:55:41 2018
 ************************************************************************/

#include<iostream>
using namespace std;

/**
* 判断一个无符号数是不是2的乘方
* 使用位运算要比普通算术运算高效的多
* 位运算的时间复杂度O(1)
* 算术运算的事件复杂度O(logN)
*/
bool isPowerOfTwo(unsigned int n)
{
    return (n & (n - 1)) == 0;
}

/**
* 判读一个数的二进制形式有几个1
*/
unsigned int getOneCount(unsigned int n)
{
    unsigned int count = 0;
    while (n > 0)
    {
        if ((n & 1) == 1)
        {
            ++count;
        }
        n = n >> 1;
    }
    return count;
}

int main()
{
    std::boolalpha(std::cout);
    std::cout << isPowerOfTwo(32) << std::endl;
    std::noboolalpha(std::cout);

    std::cout << getOneCount(7) << std::endl;
    return 0;
}
