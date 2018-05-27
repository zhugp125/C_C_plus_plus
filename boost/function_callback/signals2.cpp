/*************************************************************************
	> File Name: signals2.cpp
	> Author: 
	> Mail: 
	> Created Time: 日  5/27 16:45:50 2018
 ************************************************************************/

//g++ signals2.cpp -I/usr/local/include

#include<iostream>
#include<boost/signals2.hpp>

using namespace std;
using namespace boost::signals2;

void slots1()
{
    cout << "slot1 called\n";
}

void slots2()
{
    cout << "slot2 called\n";
}

//using group
template<int N>
struct slots
{
    void operator() ()
    {
        cout << "slots" << N << " called\n";
    }
};

//get return value
template<int N>
class calc
{
public:
    int operator() (int x)
    {
        cout << "slots" << N << " called\n";
        return x * N;
    }
};

int main()
{
    {
        signal<void()> sig;
        sig.connect(&slots1, at_front);
        sig.connect(&slots2, at_front);

        sig();
    }
    cout << "\n";

    {
        signal<void()> sig;
        sig.connect(slots<1>(), at_back);
        sig.connect(slots<100>(), at_front);

        sig.connect(6, slots<64>(), at_front);
        sig.connect(6, slots<62>(), at_back);

        sig.connect(3, slots<30>(), at_front);
        sig.connect(3, slots<36>(), at_back);

        sig.connect(8, slots<80>(), at_front);

        sig();
    }
    cout << "\n";

    {
        signal<int(int)> sig;
        sig.connect(calc<1>());
        sig.connect(calc<10>());
        sig.connect(calc<100>());

        cout << *sig(2) << endl;
    }

    return 0;
}
