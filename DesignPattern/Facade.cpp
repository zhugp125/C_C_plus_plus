#include <iostream>

using namespace std;

#define SAFE_DELETE(p) if(p) { delete p; p = nullptr; }

class Shape
{
public:
    virtual ~Shape() {}
    virtual void draw() = 0;
};

class Rectangle : public Shape
{
public:
    void draw() { cout << "shape draw(): Rectangle" << endl; }
};

class Square : public Shape
{
public:
    void draw() { cout << "shape draw(): Square" << endl; }
};

class Circle : public Shape
{
public:
    void draw() { cout << "shape draw(): Circle" << endl; }
};

class ShapeMarker
{
public:
    ShapeMarker()
        : m_rectangle(nullptr)
        , m_square(nullptr)
        , m_circle(nullptr)
    {}

    ~ShapeMarker()
    {
        SAFE_DELETE(m_rectangle)
        SAFE_DELETE(m_square)
        SAFE_DELETE(m_circle)
    }

    void drawRect()
    {
        if (nullptr == m_rectangle)
        {
            m_rectangle = new Rectangle;
        }
        m_rectangle->draw();
    }

    void drawSquare()
    {
        if (nullptr == m_square)
        {
            m_square = new Square;
        }
        m_square->draw();
    }

    void drawCircle()
    {
        if (nullptr == m_circle)
        {
            m_circle = new Circle;
        }
        m_circle->draw();
    }

private:
    Shape* m_rectangle;
    Shape* m_square;
    Shape* m_circle;
};

int main()
{
    ShapeMarker marker;
    marker.drawCircle();
    marker.drawRect();
    marker.drawSquare();

    cout << "Hello World!" << endl;
    return 0;
}
