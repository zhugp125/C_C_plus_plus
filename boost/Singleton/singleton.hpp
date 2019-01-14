#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <boost/core/noncopyable.hpp>
#include <boost/thread/once.hpp>
#include <cstdlib>

template <class T>
class Singleton : boost::noncopyable
{
public:
    static T* instance()
    {
        boost::call_once(m_once, &Singleton::init);
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
    static boost::once_flag m_once;
    static T* m_value;
};

template <class T>
boost::once_flag Singleton<T>::m_once = BOOST_ONCE_INIT;

template <class T>
T* Singleton<T>::m_value = NULL;

#endif // SINGLETON_HPP
