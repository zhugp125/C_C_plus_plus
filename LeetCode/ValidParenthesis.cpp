#include <iostream>
#include <stack>
#include <map>

using namespace std;

/**
  valid parenthesis
  (){}[] --> true
  ({[]}) --> true
  ({)}   --> false

  遇到左括号，入栈
  遇到右括号，取栈顶元素与之匹配
*/

bool isValidParenthesis(const string &str)
{
    map<char, char> rulers;
    rulers['('] = ')';
    rulers['['] = ']';
    rulers['{'] = '}';

    stack<char> parenthesis;
    for(int i = 0; i != str.size(); ++i)
    {
        if (rulers.find(str[i]) != rulers.end())
        {
            parenthesis.push(str[i]);
        }
        else
        {
            if (parenthesis.empty())
            {
                return false;
            }

            if (rulers[parenthesis.top()] != str[i])
            {
                return false;
            }
            parenthesis.pop();
        }
    }

    return parenthesis.empty();
}

int main()
{
    cout << boolalpha;
    cout << isValidParenthesis("()") << endl;
    cout << isValidParenthesis("(){}[]") << endl;
    cout << isValidParenthesis("({[]})") << endl;
    cout << isValidParenthesis("({)}") << endl;
    cout << isValidParenthesis("({)") << endl;
    cout << noboolalpha;
    cout << "Hello World!" << endl;
    return 0;
}
