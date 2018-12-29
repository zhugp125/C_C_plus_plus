#include <iostream>
#include <boost/checked_delete.hpp>
using namespace std;
using namespace boost;

//gcc CheckedDelete.cpp -I/usr/local/include -o CheckedDelete
class demo_class;

/*
 * 不建议直接操作原始内存，除非一些必须要操作原始内存的地方
*/

int main()
{
    auto p1 = new int(10);
    checked_delete(p1); // delete pointer

    auto p2 = new int[10];
    checked_array_delete(p2); // delete array pointer

    //demo_class* demo;
    //checked_delete(demo); //报错
    //delete demo; //warning

    cout << "Hello World!" << endl;
    return 0;
}
