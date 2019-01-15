#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <boost/core/noncopyable.hpp>
#include <cstdlib>
#include <mutex>

template <class T>
class Singleton : boost::noncopyable
{
public:
    static T* instance()
    {
        std::call_once(m_once, &Singleton::init);
        return m_value;
    }

private:
    static void init()
    {
        m_value = new T;
        ::atexit(&Singleton::destory);
    }

    static void destory()
    {
        delete m_value;
    }

private:
    static std::once_flag m_once;
    static T* m_value;
};

template <class T>
std::once_flag Singleton<T>::m_once;

template <class T>
T* Singleton<T>::m_value = NULL;

#endif // SINGLETON_HPP
