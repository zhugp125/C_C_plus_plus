#include <iostream>
#include <vector>
using namespace std;

class Expression
{
public:
    virtual ~Expression() {}
    virtual bool interpreter(const string& str) = 0;
};

class TerminalExpression : public Expression
{
public:
    TerminalExpression(const string& data) : m_data(data) {}
    bool interpreter(const string &str)
    {
        return str.find(m_data) < str.size();
    }

private:
    string m_data;
};

class AndExpression : public Expression
{
public:
    AndExpression(Expression* expr1, Expression* expr2)
        : m_expr1(expr1), m_expr2(expr2)
    {}

    bool interpreter(const string &str)
    {
        return m_expr1->interpreter(str) && m_expr2->interpreter(str);
    }

private:
    Expression* m_expr1;
    Expression* m_expr2;
};

class OrExpression : public Expression
{
public:
    OrExpression(Expression* expr1, Expression* expr2)
        : m_expr1(expr1), m_expr2(expr2)
    {}

    bool interpreter(const string &str)
    {
        return m_expr1->interpreter(str) || m_expr2->interpreter(str);
    }

private:
    Expression* m_expr1;
    Expression* m_expr2;
};

int main()
{
    vector<Expression* > expressions;
    Expression* john = new TerminalExpression("john");
    Expression* robet = new TerminalExpression("robet");
    Expression* orExpr = new OrExpression(john, robet);
    expressions.push_back(john);
    expressions.push_back(robet);
    expressions.push_back(orExpr);

    Expression* marry = new TerminalExpression("marry");
    Expression* maried = new TerminalExpression("maried");
    Expression* andExpr = new AndExpression(marry, maried);
    expressions.push_back(marry);
    expressions.push_back(maried);
    expressions.push_back(andExpr);

    cout << boolalpha;
    cout << "john is male? " << orExpr->interpreter("john") << endl;
    cout << "marry is maried female? " << andExpr->interpreter("marry maried") << endl;
    cout << noboolalpha;

    for (auto it = expressions.cbegin(); it != expressions.cend(); ++it)
    {
        delete *it;
    }
    expressions.clear();

    return 0;
}
