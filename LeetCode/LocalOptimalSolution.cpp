#include <iostream>
#include <list>
using namespace std;

list<int> split(int input)
{
    list<int> output;
    if (input == 0)
    {
        output.push_back(input);
    }
    else if (input > 0)
    {
        while (input > 0)
        {
            output.push_front(input % 10);
            input /= 10;
        }
    }
    return output;
}

int join(const list<int>& input)
{
    int output = 0;
    for (const auto& num : input)
    {
        output *= 10;
        output += num;
    }
    return output;
}

int removeDigits(int input, int k)
{
    if (input <= 0 || k < 0)
    {
        return input;
    }

    list<int> output = split(input);
    if (output.empty() || k >= static_cast<int>(output.size()))
    {
        return 0;
    }

    for (int i = 0; i != k; ++i)
    {
        auto preIter = output.begin();
        auto nextIter = ++(output.begin());
        for (; nextIter != output.end(); ++nextIter, ++preIter)
        {
            if (*preIter > *nextIter)
            {
                output.erase(preIter);
                break;
            }
        }
        if (nextIter == output.end())
        {
            output.pop_back();
        }
    }

    return join(output);
}

int main()
{
    cout << removeDigits(51234, 2) << endl;
    cout << "Hello World!" << endl;
    return 0;
}
