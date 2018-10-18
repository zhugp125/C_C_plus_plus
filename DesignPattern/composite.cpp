#include <iostream>
#include <string>
#include <list>

using namespace std;

class Employee
{
public:
    Employee(const string& name, const string &dept, int salary)
        : m_name(name)
        , m_dept(dept)
        , m_salary(salary)
    {}

    void add(const Employee &e)
    {
        m_employees.push_back(e);
    }

    list<Employee> getEmployees()
    {
        return m_employees;
    }

    const list<Employee>& getEmployees() const
    {
        return m_employees;
    }

    string toString()
    {
        return string("Employee :[ Name: ") + m_name + ", Dept: " + m_dept + ", salary: " + to_string(m_salary) + " ]";
    }

    const string toString() const
    {
        return string("Employee : [ Name: ") + m_name + ", Dept: " + m_dept + ", salary: " + to_string(m_salary) + " ]";
    }

private:
    string m_name;
    string m_dept;
    int m_salary;
    list<Employee> m_employees;
};

int main()
{
    Employee ceo("LDY", "CEO", 50000);

    Employee headSales("Hebe", "Head Sales", 20000);
    Employee headMarkets("LZS", "Head Markets", 24000);

    Employee sale1("sale1", "sale", 8000);
    Employee sale2("sale2", "sale", 6000);
    headSales.add(sale1);
    headSales.add(sale2);

    Employee market1("market1", "market", 10000);
    Employee market2("market2", "market", 9000);
    headMarkets.add(market1);
    headMarkets.add(market2);

    ceo.add(headSales);
    ceo.add(headMarkets);

    cout << ceo.toString() << endl;
    for (const Employee& head : ceo.getEmployees())
    {
        cout << head.toString() << endl;
        for (const Employee& e : head.getEmployees())
        {
            cout << e.toString() << endl;
        }
    }

    cout << "Hello World!" << endl;
    return 0;
}
