#include <iostream>
using namespace std;

class StudentModel
{
public:
    void setName(const string& name) { m_name = name; }
    string getName() { return m_name; }
    void setId(const int id) { m_id = id; }
    int getId() { return m_id; }

private:
    string m_name;
    int m_id;
};

class StudentView
{
public:
    StudentView() : m_model(nullptr) {}
    void setModel(StudentModel* model) { m_model = model; }
    StudentModel* getModel() { return m_model; }
    void update()
    {
        cout << "Student ID = " << m_model->getId() << ", Name = " << m_model->getName() << endl;
    }

private:
    StudentModel* m_model;
};

class StudentController
{
public:
    StudentController(StudentView* view) : m_view(view) {}

    void setName(const string& name)
    {
        m_view->getModel()->setName(name);
        m_view->update();
    }

    void setId(const int id)
    {
        m_view->getModel()->setId(id);
        m_view->update();
    }

private:
    StudentView* m_view;
};

int main()
{
    StudentModel model;
    StudentView view;
    view.setModel(&model);

    model.setId(1);
    model.setName("L");
    view.update();

    StudentController controller(&view);
    controller.setId(2);
    controller.setName("Z");

    cout << "Hello World!" << endl;
    return 0;
}
