#include <iostream>
using namespace std;

class Strategy
{
public:
    virtual ~Strategy() {}
    virtual int doOperation(int num1, int num2) = 0;
};

class OperationAdd : public Strategy
{
public:
    int doOperation(int num1, int num2)
    {
        return num1 + num2;
    }
};

class OperationSubstract : public Strategy
{
public:
    int doOperation(int num1, int num2)
    {
        return num1 - num2;
    }
};

class OperationMultiply : public Strategy
{
public:
    int doOperation(int num1, int num2)
    {
        return num1 * num2;
    }
};

class Context
{
public:
    Context() : m_strategy(nullptr) {}
    void setStrategy(Strategy* strategy) { m_strategy = strategy; }
    int excuteStrategy(int num1, int num2) { return m_strategy->doOperation(num1, num2); }

private:
    Strategy* m_strategy;
};

int main()
{
    Context context;
    OperationAdd add;
    OperationSubstract sub;
    OperationMultiply mul;
    int num1 = 10;
    int num2 = 5;

    context.setStrategy(&add);
    cout << "add" << endl;
    cout << num1 << " + " << num2 << " = " << context.excuteStrategy(num1, num2) << endl;
    cout << endl;

    context.setStrategy(&sub);
    cout << "sub" << endl;
    cout << num1 << " - " << num2 << " = " << context.excuteStrategy(num1, num2) << endl;
    cout << endl;

    context.setStrategy(&mul);
    cout << "mul" << endl;
    cout << num1 << " * " << num2 << " = " << context.excuteStrategy(num1, num2) << endl;
    cout << endl;

    cout << "Hello World!" << endl;
    return 0;
}
