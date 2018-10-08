/*************************************************************************
	> File Name: SubSort.cpp
	> Author: 朱高鹏
	> Mail: zhugp125@sina.com
	> Created Time: 一 10/ 8 21:48:50 2018
 ************************************************************************/

#include<iostream>
#include<random>
using namespace std;

#define N 20

void createData(int *arr, size_t n)
{
    default_random_engine e;
    uniform_int_distribution<unsigned> u(0, 10);
    for (int i = 0; i != n; ++i)
    {
        arr[i] = u(e);
    }
}

void print(int *arr, size_t n)
{
    for (int i = 0; i != n; ++i)
    {
        cout << arr[i] << ' ';
    }
    cout << endl;
}

void SubSort(int *arr, size_t n)
{
    /*
    * 先找出最大最小值，确定取值范围
    */
    int minNum = arr[0];
    int maxNum = arr[0];
    for (int i = 0; i != n; ++i)
    {
        if (minNum > arr[i])
        {
            minNum = arr[i];
        }
        if (maxNum < arr[i])
        {
            maxNum = arr[i];
        }
    }

    int *dest = new int[maxNum - minNum + 1]();
    for (int i = 0; i != n; ++i)
    {
        ++dest[arr[i] - minNum];
    }

    for (int i = minNum; i != maxNum + 1; ++i)
    {
        for (int j = 0; j != dest[i - minNum]; ++j)
        {
            cout << i << ' ';
        }
    }
    cout << endl;

    delete []dest;
}

int main()
{
    int arr[N] = {0};
    createData(arr, N);
    print(arr, N);

    SubSort(arr, N);

    return 0;
}
