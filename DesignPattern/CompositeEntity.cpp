#include <iostream>
using namespace std;

class Object
{
public:
    void setData(const string& data) { m_data = data; }
    string getData() { return m_data; }

private:
    string m_data;
};

class CompositeEntity
{
public:
    void setData(const string& data1, const string& data2)
    {
        m_obj1.setData(data1);
        m_obj2.setData(data2);
    }

    pair<string, string> getData()
    {
        return make_pair(m_obj1.getData(), m_obj2.getData());
    }

private:
    Object m_obj1;
    Object m_obj2;
};

class Client
{
public:
    void setData(const string& data1, const string& data2)
    {
        m_entity.setData(data1, data2);
    }

    void printData()
    {
        pair<string, string> pdata = m_entity.getData();
        cout << "object1 data = " << pdata.first << " object2 data = " << pdata.second << endl;
    }

private:
    CompositeEntity m_entity;
};

int main()
{
    Client client;
    client.setData("Hello", "World");
    client.printData();

    cout << "Hello World!" << endl;
    return 0;
}
