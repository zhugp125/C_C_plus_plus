#include <iostream>

using namespace std;

#define MAX 100

template <typename T>
class Stack
{
public:
    Stack() : m_length(0) {}

    T pop() {
        if (m_length > 0)
        {
            T data = m_data[m_length - 1];
            --m_length;
            return data;
        }
        return T();
    }

    void push(const T& data) {
        if (m_length < MAX) {
            m_data[m_length++] = data;
        }
    }

    T top() {
        if (m_length > 0)
        {
            T data = m_data[m_length - 1];
            return data;
        }
        return T();
    }

    bool empty() {
        return m_length == 0;
    }

    T min() {
        if (m_length > 0)
        {
            T minData = m_data[0];
            for (size_t i = 1; i < m_length; ++i)
            {
                if (minData > m_data[i])
                {
                    minData = m_data[i];
                }
            }
            return minData;
        }
        return T();
    }

    friend bool operator== (const Stack& lhs, const Stack& rhs)
    {
        return (lhs.m_length == rhs.m_length) && std::equal(std::begin(lhs.m_data), std::end(lhs.m_data), std::begin(rhs.m_data));
    }

    friend bool operator!= (const Stack& lhs, const Stack& rhs)
    {
        return !(lhs == rhs);
    }

    Stack& operator= (const Stack& stack)
    {
        if (*this != stack)
        {
            m_length = stack.m_length;
            memcpy(m_data, stack.m_data, stack.m_length);
        }
    }

private:
    T m_data[MAX];
    size_t m_length;
};

int main()
{
    cout << boolalpha;
    {
        Stack<int> s;
        cout << "is empty: " << s.empty() << endl;
        s.push(3);
        s.push(2);
        s.push(7);
        s.push(4);
        s.push(5);
        cout << "pop: " << s.pop() << endl;
        cout << "top: " << s.top() << endl;
        cout << "min: " << s.min() << endl;
    }

    {
        Stack<int> s;
        cout << "is empty: " << s.empty() << endl;
        cout << "pop: " << s.pop() << endl;
        cout << "top: " << s.top() << endl;
        cout << "min: " << s.min() << endl;
    }
    cout << noboolalpha;

    cout << "Hello World!" << endl;
    return 0;
}
