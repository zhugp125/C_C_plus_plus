#include <iostream>
#include <list>
#include <map>
using namespace std;

class Student
{
public:
    Student(const string& name = "", const int id = -1)
        : m_name(name)
        , m_id(id)
    {}
    void setName(const string& name) { m_name = name; }
    string getName() { return m_name; }
    void setId(const int id) { m_id = id; }
    int getId() { return m_id; }
    const int getId() const { return m_id; }

    void display()
    {
        cout << "[student] name = " << m_name << ", id = " << m_id << endl;
    }

private:
    string m_name;
    int m_id;
};

class StudentDao
{
public:
    virtual ~StudentDao() {}

    virtual list<Student> getAllStudents() = 0;
    virtual Student getStudent(int id) = 0;
    virtual void updateStudent(const Student& stu) = 0;
    virtual void deleteStudent(const int id) = 0;
};

class StudentDaoImpl : public StudentDao
{
public:
    StudentDaoImpl()
    {
        {
            Student stu("Liu", 0);
            m_students[stu.getId()] = stu;
        }
        {
            Student stu("zhu", 1);
            m_students[stu.getId()] = stu;
        }
    }

    list<Student> getAllStudents()
    {
        list<Student> studentList;
        for (auto it = m_students.begin(); it != m_students.end(); ++it)
        {
            studentList.push_back(it->second);
        }
        return studentList;
    }

    Student getStudent(int id)
    {
        auto it = m_students.find(id);
        if (it != m_students.end())
        {
            return it->second;
        }
        return Student();
    }

    void updateStudent(const Student& stu)
    {
        auto it = m_students.find(stu.getId());
        if (it != m_students.end())
        {
            it->second = stu;
        }
    }

    void deleteStudent(const int id)
    {
        auto it = m_students.find(id);
        if (it != m_students.end())
        {
            m_students.erase(it);
        }
    }

private:
    map<int, Student> m_students;
};

int main()
{
    StudentDaoImpl daoImpl;
    for (auto stu : daoImpl.getAllStudents())
    {
        stu.display();
    }
    cout << endl;

    Student stu = daoImpl.getStudent(0);
    stu.setName("zhang");
    daoImpl.updateStudent(stu);

    for (auto stu : daoImpl.getAllStudents())
    {
        stu.display();
    }
    cout << endl;

    daoImpl.deleteStudent(0);
    for (auto stu : daoImpl.getAllStudents())
    {
        stu.display();
    }
    cout << endl;

    cout << "Hello World!" << endl;
    return 0;
}
