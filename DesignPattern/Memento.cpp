#include <iostream>
#include <vector>
using namespace std;

class Memento
{
public:
    Memento(const string& state) : m_state(state) {}
    void setState(const string& state) { m_state = state; }
    string getState() { return m_state; }

private:
    string m_state;
};

class Originator
{
public:
    void setState(const string& state) { m_state = state; }
    string getState() { return m_state; }
    Memento saveStateToMemento() { return Memento(m_state); }
    void getStateFromMemento(Memento memento) { m_state = memento.getState(); }

private:
    string m_state;
};

class CareTaker
{
public:
    void add(Memento memento) { m_mementos.push_back(memento); }
    Memento get(int index) { return m_mementos.at(index); }

private:
    vector<Memento> m_mementos;
};

int main()
{
    Originator originator;
    CareTaker careTaker;
    originator.setState("State #1");
    originator.setState("State #2");
    careTaker.add(originator.saveStateToMemento());
    originator.setState("State #3");
    careTaker.add(originator.saveStateToMemento());
    originator.setState("State #4");

    cout << "Current State: " << originator.getState() << endl;
    originator.getStateFromMemento(careTaker.get(0));
    cout << "First saved State: " << originator.getState() << endl;
    originator.getStateFromMemento(careTaker.get(1));
    cout << "Second saved State: " << originator.getState() << endl;

    cout << "Hello World!" << endl;
    return 0;
}
