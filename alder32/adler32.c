/*************************************************************************
	> File Name: adler32.c
	> Author: 
	> Mail: 
	> Created Time: 三  5/30 22:58:33 2018
 ************************************************************************/

#include "adler32.h"
const int MOD_ADLER = 65521;

unsigned long adler32(const char* data, int len)
{
    unsigned long a = 1, b = 0;
    int index;

    for (index = 0; index < len; ++index)
    {
        a = (a + data[index]) % MOD_ADLER;
        b = (b + a) % MOD_ADLER;
    }

    return (b << 16) | a;
}

