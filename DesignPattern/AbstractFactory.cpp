/*************************************************************************
	> File Name: AbstractFactory.cpp
	> Author: 
	> Mail: 
	> Created Time: 日 10/ 7 20:42:10 2018
 ************************************************************************/

#include<iostream>
using namespace std;

enum E_SHAPE
{
    S_RECT,
    S_SQUARE,
    S_CIRCLE,
};

enum E_COLOR
{
    C_RED,
    C_GREEN,
    C_WHITE,
};

enum FactoryType
{
    FT_SHAPE,
    FT_COLOR,
};

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
        cout << "shape draw(): Rectangle" << endl;
    }
};

class Square : public Shape
{
public:
    void draw()
    {
        cout << "shape draw(): Square" << endl;
    }
};

class Circle : public Shape
{
public:
    void draw()
    {
        cout << "shape draw(): Circle" << endl;
    }
};

class Color
{
public:
    virtual ~Color() {}
    virtual void fill() = 0;
};

class Red : public Color
{
public:
    void fill()
    {
        cout << "color fill(): Red" << endl;
    }
};

class Green : public Color
{
public:
    void fill()
    {
        cout << "color fill(): Green" << endl;
    }
};

class White : public Color
{
public:
    void fill()
    {
        cout << "color fill(): White" << endl;
    }
};

/*
 * 抽象工厂基类*
*/
class AbstractFactory
{
public:
    virtual ~AbstractFactory() {}
    virtual Shape* getShape(E_SHAPE) { return NULL; }
    virtual Color* getColor(E_COLOR) { return NULL; }
};

/*
* Shape工厂类 
*/
class ShapeFactory : public AbstractFactory
{
public:
    Shape* getShape(E_SHAPE _type)
    {
        if (S_RECT == _type)
        {
            return new Rectangle();
        }
        else if (S_SQUARE == _type)
        {
            return new Square();
        }
        else if (S_CIRCLE == _type)
        {
            return new Circle();
        }
        return NULL;
    }
};

/*
* color工厂类
*/
class ColorFactory : public AbstractFactory
{
public:
    Color* getColor(E_COLOR _type)
    {
        if (C_RED == _type)
        {
            return new Red();
        }
        else if (C_GREEN == _type)
        {
            return new Green();
        }
        else if (C_WHITE == _type)
        {
            return new White();
        }
        return NULL;
    }
};

/*
* 抽象基类工厂生成器
*/
class FactoryProducer
{
public:
    AbstractFactory* create(FactoryType _type)
    {
        if (FT_SHAPE == _type)
        {
            return new ShapeFactory();
        }
        else if (FT_COLOR == _type)
        {
            return new ColorFactory();
        }
        return NULL;
    }
};

int main()
{
    FactoryProducer producer;
    AbstractFactory* shapeFactory = producer.create(FT_SHAPE);
    if (NULL != shapeFactory)
    {
        Shape* rect = shapeFactory->getShape(S_RECT);
        if (NULL != rect)
        {
            rect->draw();
            delete rect;
        }

        Shape* square = shapeFactory->getShape(S_SQUARE);
        if (NULL != square)
        {
            square->draw();
            delete square;
        }

        Shape* circle = shapeFactory->getShape(S_CIRCLE);
        if (NULL != circle)
        {
            circle->draw();
            delete circle;
        }
        delete shapeFactory;
    }

    AbstractFactory* colorFactory = producer.create(FT_COLOR);
    if (NULL != colorFactory)
    {
        Color* red = colorFactory->getColor(C_RED);
        if (NULL != red)
        {
            red->fill();
            delete red;
        }

        Color* green = colorFactory->getColor(C_GREEN);
        if (NULL != green)
        {
            green->fill();
            delete green;
        }

        Color* white = colorFactory->getColor(C_WHITE);
        if (NULL != white)
        {
            white->fill();
            delete white;
        }
        delete colorFactory;
    }
    return 0;
}
