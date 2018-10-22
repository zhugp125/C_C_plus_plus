#include <iostream>
#include <map>
#include <random>
using namespace std;

class Circle
{
public:
    Circle() : m_x(0), m_y(0), m_radius(0) {}

    void draw() { cout << "circle x = " << m_x << " y = " << m_y << " radius = " << m_radius << " color = " << m_color << endl; }
    void setX(int x) { m_x = x; }
    void setY(int y) { m_y = y; }
    void setRadius(int radius) { m_radius = radius; }
    void setColor(const string& color) { m_color = color; }

private:
    int m_x;
    int m_y;
    int m_radius;
    string m_color;
};

class ShapeFactory
{
public:
    ~ShapeFactory()
    {
        for (auto it = m_circles.cbegin(); it != m_circles.cend(); ++it)
        {
            delete it->second;
        }
    }

    Circle* getCircle(const string& color)
    {
        Circle* circle = m_circles[color];
        if (nullptr == circle)
        {
            circle = new Circle;
            circle->setColor(color);
            m_circles[color] = circle;
        }
        return circle;
    }

private:
    map<string, Circle*> m_circles;
};

int main()
{
    string colors[] = {"red", "green", "yellow", "blue", "black"};
    ShapeFactory factory;

    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<int> dist(1, 20);
    std::uniform_int_distribution<int> indexs(0, 4);
    for (int i = 0; i != 20; ++i)
    {
        Circle* circle = factory.getCircle(colors[indexs(rng)]);
        circle->setX(dist(rng));
        circle->setY(dist(rng));
        circle->setRadius(10);
        circle->draw();
    }

    cout << "Hello World!" << endl;
    return 0;
}
