#include <iostream>
#include <vector>
using namespace std;

class ComputerPartVoistor;
class ComputerPart
{
public:
    virtual ~ComputerPart() {}
    virtual void accept(ComputerPartVoistor*) = 0;
};

class Computer;
class Mouse;
class Keyboard;
class Monitor;
class ComputerPartVoistor
{
public:
    virtual ~ComputerPartVoistor() {}
    virtual void visit(Computer*) = 0;
    virtual void visit(Mouse*) = 0;
    virtual void visit(Keyboard*) = 0;
    virtual void visit(Monitor*) = 0;
};

class Mouse : public ComputerPart
{
public:
    void accept(ComputerPartVoistor* visitor)
    {
        visitor->visit(this);
    }
};

class Keyboard : public ComputerPart
{
public:
    void accept(ComputerPartVoistor* visitor)
    {
        visitor->visit(this);
    }
};

class Monitor : public ComputerPart
{
public:
    void accept(ComputerPartVoistor* visitor)
    {
        visitor->visit(this);
    }
};

class Computer : public ComputerPart
{
public:
    Computer()
    {
        m_computerParts.push_back(new Mouse);
        m_computerParts.push_back(new Keyboard);
        m_computerParts.push_back(new Monitor);
    }
    ~Computer()
    {
        for (auto it = m_computerParts.begin(); it != m_computerParts.end(); ++it)
        {
            delete (*it);
        }
    }

    void accept(ComputerPartVoistor* visitor)
    {
        for (auto it = m_computerParts.begin(); it != m_computerParts.end(); ++it)
        {
            (*it)->accept(visitor);
        }
        visitor->visit(this);
    }

private:
    vector<ComputerPart*> m_computerParts;
};

class ComputerPartDisplayVoistor : public ComputerPartVoistor
{
public:
    virtual void visit(Computer*)
    {
        cout << "display computer" << endl;
    }
    virtual void visit(Mouse*)
    {
        cout << "display mouse" << endl;
    }
    virtual void visit(Keyboard*)
    {
        cout << "display keyboard" << endl;
    }
    virtual void visit(Monitor*)
    {
        cout << "display monitor" << endl;
    }
};

int main()
{
    Computer computer;
    ComputerPartDisplayVoistor visitor;
    computer.accept(&visitor);

    cout << "Hello World!" << endl;
    return 0;
}
