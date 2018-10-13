#include <iostream>
#include <map>

using namespace std;

class Shape
{
public:
    Shape() {}
    void setId(int id) { m_id = id; }
    int getId() { return m_id; }

    virtual void draw() = 0;

private:
    int m_id;
};

class Rectangle : public Shape
{
public:
    void draw() { cout << "[Rectangle][draw()]..." << endl; }
};

class Square : public Shape
{
public:
    void draw() { cout << "[Square][draw()]..." << endl; }
};

class Circle : public Shape
{
public:
    void draw() { cout << "[Circle][draw()]..." << endl; }
};

class ShapeCache
{
public:
    void load()
    {
        Shape* rect = new Rectangle();
        rect->setId(0);
        m_data.insert(make_pair(rect->getId(), rect));

        Shape* square = new Square();
        square->setId(1);
        m_data.insert(make_pair(square->getId(), square));

        Shape* circle = new Circle();
        circle->setId(2);
        m_data.insert(make_pair(circle->getId(), circle));
    }

    Shape* getShape(int id)
    {
         map<int, Shape*>::iterator it = m_data.find(id);
         if (it != m_data.end())
         {
             return it->second;
         }
         return nullptr;
    }

private:
    map<int, Shape*> m_data;
};

int main()
{
    ShapeCache cache;
    cache.load();
    cache.getShape(0)->draw();
    cache.getShape(1)->draw();
    cache.getShape(2)->draw();

    cout << endl;
    cout << "Hello World!" << endl;
    return 0;
}
