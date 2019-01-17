#ifndef RINGBUFFER_HPP
#define RINGBUFFER_HPP

#include <deque>
#include <mutex>
#include <condition_variable>
#include <assert.h>

template <class T>
class RingBuffer
{
public:
    T take()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        while (m_datas.empty()) {
            m_cond.wait(lock);
        }
        assert(!m_datas.empty());
        T value(m_datas.front());
        m_datas.pop_front();
        return value;
    }

    void push(const T & value)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_datas.push_back(value);
        m_cond.notify_one();
    }

    // c++11
    void push(T && value)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_datas.push_back(value);
        m_cond.notify_one();
    }

    size_t size() const
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_datas.size();
    }

private:
    mutable std::mutex m_mutex;
    std::condition_variable m_cond;
    std::deque<T> m_datas;
};

#endif // RINGBUFFER_HPP
