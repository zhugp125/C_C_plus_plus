#include <iostream>
using namespace std;

class State;
class Context
{
public:
    Context() : m_state(nullptr) {}
    void setState(State* state) { m_state = state;}
    State* getState() { return m_state; }

private:
    State* m_state;
};

class State
{
public:
    virtual ~State() {}
    virtual void doAction(Context* context) = 0;
    virtual string toString() = 0;
};

class StartState : public State
{
public:
    void doAction(Context* context)
    {
        cout << "player is in start state" << endl;
        context->setState(this);
    }

    string toString() { return "Start state"; }
};

class StopState : public State
{
public:
    void doAction(Context* context)
    {
        cout << "player is in stop state" << endl;
        context->setState(this);
    }

    string toString() { return "Stop state"; }
};

int main()
{
    Context context;
    {
        State* state = new StartState;
        state->doAction(&context);
        cout << context.getState()->toString() << endl;
        delete state;
    }
    {
        State* state = new StopState;
        state->doAction(&context);
        cout << context.getState()->toString() << endl;
        delete state;
    }

    cout << "Hello World!" << endl;
    return 0;
}
