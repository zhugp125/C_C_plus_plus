#include <iostream>
#include <vector>

using namespace std;

class CStringList
{
public:
    void append(const string& str)
    {
        m_strList.push_back(str);
    }

    string join(const string& seq)
    {
        if (m_strList.empty())
        {
            return "";
        }
        string result = m_strList[0];
        for (int i = 1; i < m_strList.size(); ++i)
        {
            result += seq;
            result += m_strList[i];
        }
        return result;
    }

private:
    vector<string> m_strList;
};

class Bulider
{
public:
    void append(const string& str)
    {
        m_bulider.append(str);
    }

    CStringList bulider()
    {
        return m_bulider;
    }

private:
    CStringList m_bulider;
};

int main()
{
    Bulider bulider;
    bulider.append("hello");
    bulider.append("world");
    CStringList strList = bulider.bulider();
    cout << strList.join(",") << endl;
    cout << "Hello World!" << endl;
    return 0;
}
