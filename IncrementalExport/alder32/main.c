/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 三  5/30 23:04:42 2018
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include "adler32.h"

int main()
{
    char* s1 = "0x0201";
    printf("%ld\n", adler32(s1, strlen(s1)));
    char* s2 = "0x0120";
    printf("%ld\n", adler32(s2, strlen(s2)));

    return 0;
}
