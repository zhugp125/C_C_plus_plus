#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class AbstractCustomer
{
public:
    AbstractCustomer(const string& name) : m_name(name) {}
    virtual ~AbstractCustomer() {}
    virtual bool isNull() = 0;
    virtual string getName() = 0;

protected:
    string m_name;
};

class RealCustomer : public AbstractCustomer
{
public:
    RealCustomer(const string& name) :AbstractCustomer(name) {}
    bool isNull() { return false; }
    string getName() { return m_name; }
};

class NullCustomer : public AbstractCustomer
{
public:
    NullCustomer(const string& name) :AbstractCustomer(name) {}
    bool isNull() { return true; }
    string getName() { return string("null object name: ") + m_name; }
};

class CustomerFactory
{
public:
    CustomerFactory()
    {
        m_strVec.push_back("hebe");
        m_strVec.push_back("SL");
        m_strVec.push_back("LDY");
    }
    ~CustomerFactory()
    {
        for (auto it = m_customers.begin(); it != m_customers.end(); ++it)
        {
            delete it->second;
        }
        m_customers.clear();
    }

    AbstractCustomer* getCustomer(const string& strType)
    {
        auto it = m_customers.find(strType);
        if (it != m_customers.end())
        {
            return it->second;
        }

        AbstractCustomer* customer = nullptr;
        if (find(m_strVec.begin(), m_strVec.end(), strType) != m_strVec.end())
        {
            customer = new RealCustomer(strType);
        }
        else
        {
            customer = new NullCustomer(strType);
        }
        m_customers[strType] = customer;

        return customer;
    }

private:
    vector<string> m_strVec;
    map<string, AbstractCustomer*> m_customers;
};

int main()
{
    CustomerFactory factory;
    vector<string> vec;
    vec.push_back("hebe");
    vec.push_back("SL");
    vec.push_back("LDY");
    vec.push_back("sss");

    for(auto it = vec.begin(); it != vec.end(); ++it)
    {
        AbstractCustomer* customer = factory.getCustomer(*it);
        cout << "******************************" << endl;
        cout << "is null object? " << (customer->isNull() ? "true" : "false") << endl;
        cout << customer->getName() << endl;
        cout << endl;
    }

    cout << "Hello World!" << endl;
    return 0;
}
