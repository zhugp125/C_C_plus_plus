#include <iostream>
#include <memory>
using namespace std;

/*
 * std::addressof c++11 加入
 * addressof总能获取对象的真实地址
 *
 * 使用建议
 * 库开发者应避免重载operator&
 * 库使用者可以采用addressof获取对象的真实地址
*/

struct demo
{
    int x;
    int y;

    size_t operator&() const
    { return (size_t)&y; }
};

int main()
{
    int i = 0;
    string s;
    assert(&i == addressof(i));
    assert(&s == addressof(s));

    int a[10] = {0};
    assert(&a == addressof(a));
    assert(a + 1 == addressof(a[1]));
    assert(&printf == addressof(printf));

    demo d;
    assert(&d != (size_t)addressof(d));
    assert(&d == (size_t)&d.y);

    cout << "Hello World!" << endl;
    return 0;
}
