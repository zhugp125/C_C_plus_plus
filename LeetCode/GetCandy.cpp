#include <iostream>

using namespace std;

int getCandy(unsigned int nMoney)
{
    if (nMoney == 0)
    {
        throw std::runtime_error("input error");
    }

    int nCandy = nMoney;
    int nPaper = nMoney;
    do
    {
        nCandy += nPaper / 3;
        nPaper = nPaper / 3 + nPaper % 3;
    }while (nPaper >= 3);

    return nCandy;
}

int main()
{
    try
    {
        getCandy(0);
    }
    catch (const std::runtime_error& e)
    {
        cout << e.what() << endl;
    }

    cout << getCandy(2) << endl;
    cout << getCandy(3) << endl;
    cout << getCandy(9) << endl;
    cout << getCandy(10) << endl;

    cout << "Hello World!" << endl;
    return 0;
}
