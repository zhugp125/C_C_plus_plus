#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

class Subject;
class Observer
{
public:
    Observer(Subject* sub) : m_sub(sub) {}
    virtual ~Observer() {}
    virtual void update() = 0;

protected:
    Subject* m_sub;
};

class Subject
{
public:
    void attach(Observer* obj) { m_observers.push_back(obj); }
    void notifyAll()
    {
        for (Observer* obj : m_observers)
        {
            obj->update();
        }
    }
    void setState(int state)
    {
        m_state = state;
        notifyAll();
    }
    int getState() { return m_state; }

private:
    int m_state;
    vector<Observer*> m_observers;
};

class BinaryObserver : public Observer
{
public:
    BinaryObserver(Subject* sub) : Observer(sub) { m_sub->attach(this); }
    void update()
    {
        cout << "binary string: ";
        cout << bitset<8>(m_sub->getState()) << endl;
    }
};

class OctalObserver : public Observer
{
public:
    OctalObserver(Subject* sub) : Observer(sub) { m_sub->attach(this); }
    void update()
    {
        cout << "octal string: ";
        cout << oct << m_sub->getState() << dec << endl;
    }
};

class HexaObserver : public Observer
{
public:
    HexaObserver(Subject* sub) : Observer(sub) { m_sub->attach(this); }
    void update()
    {
        cout << "hexa string: ";
        cout << hex << m_sub->getState() << dec << endl;
    }
};

int main()
{
    Subject sub;
    BinaryObserver binary(&sub);
    OctalObserver octal(&sub);
    HexaObserver hexa(&sub);

    cout << 125 << endl;
    sub.setState(125);
    cout << 14 << endl;
    sub.setState(14);

    cout << "Hello World!" << endl;
    return 0;
}
