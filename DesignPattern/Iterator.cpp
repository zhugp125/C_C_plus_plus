#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class NameContaier
{
public:
    typedef typename vector<T>::iterator Iter;
public:
    void append(const T& t) { m_datas.push_back(t); }
    Iter begin() { return m_datas.begin(); }
    Iter end() { return m_datas.end(); }

private:
    vector<T> m_datas;
};

int main()
{
    NameContaier<string> container;
    container.append("Hello");
    container.append("World");
    container.append("Iterator");

    for (auto it = container.begin(); it != container.end(); ++it)
    {
        cout << *it << endl;
    }

    cout << "Hello World!" << endl;
    return 0;
}
