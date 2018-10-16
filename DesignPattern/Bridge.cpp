#include <iostream>

using namespace std;

class DrawAPI
{
public:
    virtual void draw(const int radius, const int x, const int y) = 0;
    virtual ~DrawAPI() {}
};

class RedCircle : public DrawAPI
{
public:
    void draw(const int radius, const int x, const int y)
    {
        cout << "Red Circle: radius: " << radius << " [ x=" << x << ", y=" << y << " ]\n";
    }
};

class GreenCircle : public DrawAPI
{
public:
    void draw(const int radius, const int x, const int y)
    {
        cout << "Green Circle: radius: " << radius << " [ x=" << x << ", y=" << y << " ]\n";
    }
};

class Shape
{
public:
    Shape(DrawAPI* drawApi) :m_drawApi(drawApi) {}
    virtual ~Shape() {}

    virtual void draw() = 0;

protected:
    DrawAPI* m_drawApi;
};

class Circle : public Shape
{
public:
    Circle(int radius, int x, int y, DrawAPI* drawApi)
        : Shape(drawApi)
        , m_radius(radius)
        , m_x(x)
        , m_y(y)
    {}

    void draw()
    {
        m_drawApi->draw(m_radius, m_x, m_y);
    }

private:
    int m_radius;
    int m_x;
    int m_y;
};

int main()
{
    DrawAPI* redDrawApi = new RedCircle;
    Shape* redShape = new Circle(10, 0, 0, redDrawApi);
    redShape->draw();
    delete redDrawApi;
    delete redShape;

    DrawAPI* greenDrawApi = new GreenCircle;
    Shape* greenShape = new Circle(5, 5, 5, greenDrawApi);
    greenShape->draw();
    delete greenDrawApi;
    delete greenShape;

    cout << "Hello World!" << endl;
    return 0;
}
