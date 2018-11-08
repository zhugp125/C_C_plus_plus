#include <iostream>
#include <map>
#include <vector>
using namespace std;

class StudentVO
{
public:
    StudentVO(const string& name, int id) : m_id(id), m_name(name) {}
    void setName(const string& name) { m_name = name; }
    string getName() { return m_name; }
    int getId() const { return m_id; }

private:
    int m_id;
    string m_name;
};

class StudentBO
{
public:
    StudentBO()
    {
        {
            StudentVO stu("liu", 1);
            m_students[stu.getId()] = stu;
        }
        {
            StudentVO stu("zhu", 2);
            m_students[stu.getId()] = stu;
        }
    }

    vector<StudentVO> getAllStudents()
    {
        vector<StudentVO> vec;
        for(auto stu : m_students)
        {
            vec.push_back(stu.second);
        }
        return vec;
    }

    void updateStudent(const StudentVO& stu)
    {
        auto it = m_students.find(stu.getId());
        if (it != m_students.cend())
        {
            m_students[stu.getId()] = stu;
        }
    }

    void deleteStudent(int id)
    {
        auto it = m_students.find(id);
        if (it != m_students.end())
        {
            m_students.erase(it);
        }
    }

    void addStudent(const StudentVO& stu)
    {
        m_students[stu.getId()] = stu;
    }

    StudentVO getStudent(int id)
    {
        auto it = m_students.find(id);
        if (it != m_students.end())
        {
            return m_students[id];
        }
        return StudentVO("", -1);
    }

private:
    map<int, StudentVO> m_students;
};

int main()
{
    StudentBO studentBusinessObject;
    for (auto stu : studentBusinessObject.getAllStudents())
    {
        cout << "[student info] id = " << stu.getId() << ", name = " << stu.getName() << endl;
    }

    StudentVO stu = studentBusinessObject.getStudent(0);
    stu.setName("zhang");
    studentBusinessObject.updateStudent(stu);

    cout << "Hello World!" << endl;
    return 0;
}
