#include <iostream>
using namespace std;

class Image
{
public:
    virtual ~Image() {}
    virtual void display() = 0;
};

class RealImage : public Image
{
public:
    RealImage(const string& fileName) : m_fileName(fileName)
    {
        loadFromDisk(m_fileName);
    }

    void display()
    {
        cout << "display: " << m_fileName << endl;
    }

private:
    void loadFromDisk(const string& fileName)
    {
        cout << "load from disk: " << fileName << endl;
    }

private:
    string m_fileName;
};

class ProxyImage : public Image
{
public:
    ProxyImage(const string& fileName)
        : m_fileName(fileName)
        , m_realImage(nullptr)
    {}

    ~ProxyImage()
    {
        if (m_realImage != nullptr)
        {
            delete m_realImage;
            m_realImage = nullptr;
        }
    }

    void display()
    {
        if (nullptr == m_realImage)
        {
            m_realImage = new RealImage(m_fileName);
        }
        m_realImage->display();
    }

private:
    string m_fileName;
    RealImage* m_realImage;
};

int main()
{
    Image* proxyImage = new ProxyImage("C++ Primer 5th");
    proxyImage->display();
    cout << "" << endl;
    proxyImage->display();
    delete proxyImage;

    cout << "Hello World!" << endl;
    return 0;
}
