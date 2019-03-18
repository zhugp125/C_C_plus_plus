#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

/**
 * 输入不少于三个数字，返回与其他数字奇偶性不同的数字
*/
int findOutlier(const std::vector<int>& arr)
{
    if (arr.size() < 3)
    {
        throw std::length_error("input size must greater than 3");
    }

    for (unsigned int i = 1; i < arr.size() -1; ++i)
    {
        bool bPrev = (arr[i - 1] % 2) == 0;
        bool bCurr = (arr[i] % 2) == 0;
        bool bNext = (arr[i + 1] % 2) == 0;

        if (bPrev == bCurr)
        {
            if (bCurr != bNext)
                return arr[i + 1];
        }
        else
        {
            if (bPrev == bNext)
                return arr[i];
            if (bCurr == bNext)
                return arr[i - 1];
        }
    }
    return 0;
}

int main()
{
    assert(findOutlier({2, 3, 4}) == 3);
    assert(findOutlier({1, 2, 3}) == 2);
    assert(findOutlier({4, 1, 3, 5, 9}) == 4);

    cout << "Hello World!" << endl;
    return 0;
}
