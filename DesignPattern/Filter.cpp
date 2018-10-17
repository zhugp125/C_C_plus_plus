#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person
{
public:
    Person(const string& name, int age, char sex)
        : m_name(name)
        , m_age(age)
        , m_sex(sex)
    {}

    string getName() const { return m_name; }
    int getAge() const { return m_age; }
    char getSex() const { return m_sex; }

private:
    string m_name;
    int m_age;
    char m_sex;
};

class Filter
{
public:
    virtual vector<Person> filter(const vector<Person>& persons) = 0;
};

class FilterName : public Filter
{
public:
    FilterName(const string& name)
        : m_name(name)
    {}

    virtual vector<Person> filter(const vector<Person>& persons)
    {
        vector<Person> result;
        result.reserve(persons.size());

        for (auto it = persons.begin(); it != persons.end(); ++it)
        {
            if (it->getName() == m_name)
            {
                result.push_back(*it);
            }
        }
        return result;
    }

private:
    string m_name;
};

class FilterAge : public Filter
{
public:
    FilterAge(int age)
        : m_age(age)
    {}

    virtual vector<Person> filter(const vector<Person>& persons)
    {
        vector<Person> result;
        result.reserve(persons.size());

        for (auto it = persons.begin(); it != persons.end(); ++it)
        {
            if (it->getAge() == m_age)
            {
                result.push_back(*it);
            }
        }
        return result;
    }

private:
    int m_age;
};

class FilterSex : public Filter
{
public:
    FilterSex(char sex)
        : m_sex(sex)
    {}

    virtual vector<Person> filter(const vector<Person>& persons)
    {
        vector<Person> result;
        result.reserve(persons.size());

        for (auto it = persons.begin(); it != persons.end(); ++it)
        {
            if (it->getSex() == m_sex)
            {
                result.push_back(*it);
            }
        }
        return result;
    }

private:
    char m_sex;
};

void printPerson(const vector<Person>& persons)
{
    for (auto it = persons.begin(); it != persons.end(); ++it)
    {
        cout << "Person: [ name: " << it->getName() << ", age: " << it->getAge() << ", sex: " << it->getSex() << " ]\n";
    }
}

class FilterDemo
{
public:
    FilterDemo(Filter* filter)
        : m_filter(filter)
    {}

    void changeFilter(Filter* filter)
    {
        m_filter = filter;
    }

    void filter(const vector<Person>& persons)
    {
        printPerson(m_filter->filter(persons));
    }

private:
    Filter* m_filter;
};

int main()
{
    vector<Person> persons;
    persons.push_back(Person("zhangsan", 26, 'f'));
    persons.push_back(Person("zhangsan", 24, 'm'));
    persons.push_back(Person("zhangsan", 32, 'f'));
    persons.push_back(Person("lisi", 26, 'f'));
    persons.push_back(Person("lisi", 26, 'm'));
    persons.push_back(Person("zhaoliu", 23, 'f'));

    FilterName filterName("zhangsan");
    FilterDemo demo(&filterName);
    cout << "FilterName" << endl;
    demo.filter(persons);

    FilterAge filterAge(26);
    demo.changeFilter(&filterAge);
    cout << "FilterAge" << endl;
    demo.filter(persons);

    FilterSex filterSex('f');
    demo.changeFilter(&filterSex);
    cout << "FilterSex" << endl;
    demo.filter(persons);

    cout << "Hello World!" << endl;
    return 0;
}
