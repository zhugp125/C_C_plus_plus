#include <iostream>
using namespace std;

class Shape
{
public:
    virtual ~Shape() {}
    virtual void draw() = 0;
};

class Rectangle : public Shape
{
public:
    void draw()
    {
        cout << "[Rectangle] [draw]" << endl;
    }
};

class Circle : public Shape
{
public:
    void draw()
    {
        cout << "[Circle] [draw]" << endl;
    }
};

class ShapeDecorator
{
public:
    void setShape(Shape* shape) { m_shape = shape; }
    virtual void draw() { m_shape->draw(); }

private:
    Shape* m_shape;
};

class RedShapeDecorator : public ShapeDecorator
{
public:
    void draw()
    {
        setColor();
        ShapeDecorator::draw();
    }

private:
    void setColor() { cout << "Red Color" << endl; }
};

int main()
{
    Shape* rect = new Rectangle();
    rect->draw();
    cout << endl;

    Shape* circle = new Circle();
    circle->draw();
    cout << endl;

    ShapeDecorator decorator;
    decorator.setShape(rect);
    decorator.draw();
    cout << endl;

    RedShapeDecorator redDecorator;
    redDecorator.setShape(circle);
    redDecorator.draw();
    cout << endl;

    cout << "Hello World!" << endl;
    return 0;
}
