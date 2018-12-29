/**
  compressed pair
  g++ CompressedPair -I/usr/local/include -o compressed_pair
*/

#include <iostream>
#include <boost/compressed_pair.hpp>
using namespace std;
using namespace boost;

class empty_test {};

int main()
{
    typedef compressed_pair<int, string> pair_type;
    {
        pair_type cp;
        cout << cp.first() << " " << cp.second() << endl;
    }
    {
        pair_type cp(10);
        cout << cp.first() << " " << cp.second() << endl;
    }
    {
        pair_type cp("string");
        cout << cp.first() << " " << cp.second() << endl;
    }
    {
        pair_type cp(20, "pair");
        cout << cp.first() << " " << cp.second() << endl;
    }

    cout << sizeof(compressed_pair<int, empty_test>) << endl; // 4
    cout << sizeof(pair<int, empty_test>) << endl;            // 8

    cout << sizeof(compressed_pair<empty_test, empty_test>) << endl; // 2
    cout << sizeof(pair<empty_test, empty_test>) << endl;            // 2

    cout << "Hello World!" << endl;
    return 0;
}
