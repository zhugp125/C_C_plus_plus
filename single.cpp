/*************************************************************************
	> File Name: single.cpp
	> Author: 
	> Mail: 
	> Created Time: 三  5/23 00:02:38 2018
 ************************************************************************/

#include <iostream>
#include <mutex>

using namespace std;
mutex mu;

/**
* 单例模式，非线程安全
*/
class Single
{
private:
    Single() {}

    static Single* m_instance;

public:
    static Single* instance()
    {
        if (NULL == m_instance)
        {
            m_instance = new Single();
        }
        return m_instance;
    }
};
Single* Single::m_instance = NULL;

/**
 * 单利模式，线程安全一
*/
class ThreadSingle
{
private:
    ThreadSingle() {}

    static ThreadSingle* m_instance;

    public:
    static ThreadSingle* instance()
    {
        if (NULL == m_instance)
        {
            lock_guard<mutex> lock(mu);
            if (NULL == m_instance)
            {
                m_instance = new ThreadSingle();
            }
        }
        return m_instance;
    }
};
ThreadSingle* ThreadSingle::m_instance = NULL;

/**
 * 单利模式，线程安全二
*/
class ThreadVolatileSingle
{
private:
    ThreadVolatileSingle() {}

    volatile static ThreadVolatileSingle* m_instance;

public:
    volatile static ThreadVolatileSingle* instance()
    {
        if (NULL == m_instance)
        {
            lock_guard<mutex> lock(mu);
            if (NULL == m_instance)
            {
                m_instance = new ThreadVolatileSingle();
            }
        }
        return m_instance;
    }
};
volatile ThreadVolatileSingle* ThreadVolatileSingle::m_instance = NULL;

int main()
{
    return 0;
}
