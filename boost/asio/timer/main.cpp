#include <iostream>
#include <boost/asio/deadline_timer.hpp>
#include <boost/system/system_error.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>

using namespace std;

void deadline_handler(const boost::system::error_code &error)
{
    if (error)
    {
        return;
    }
    cout << "hello asio" << endl;
}

// 异步定时器
void async_timer()
{
    using namespace boost::asio;
    io_service server;
    deadline_timer t(server, boost::posix_time::milliseconds(1000));
    t.async_wait(&deadline_handler);
    server.run();

    cout << "Hello World!" << endl;
}

// 同步定时器
void timer()
{
    using namespace boost::asio;
    io_service server;
    deadline_timer t(server, boost::posix_time::milliseconds(1000));
    t.wait();
    server.run();
    boost::system::error_code error;
    deadline_handler(error);

    cout << "Hello World!" << endl;
}

void timer_thread()
{
    boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
    boost::system::error_code error;
    deadline_handler(error);

    cout << "Hello World!" << endl;
}

// 类似QTimer的定时器
class Timer
{
    typedef void(* handler)();
public:
    Timer()
        : m_millseconds(1000)
        , m_timer(m_service, boost::posix_time::milliseconds(0))
        , m_handler(NULL)
        , m_tick(6)
    {}

    /**
     * @brief start  启动定时器
     * @param time   定时间隔，毫秒为单位
     */
    void start(int time = 1000)
    {
        m_millseconds = time;
        update();

        boost::system::error_code error;
        m_service.run(error);
    }

    /**
     * @brief stop 停止定时器
     */
    void stop()
    {
        m_timer.cancel();
        m_service.stop();
    }

    /**
     * @brief setHandle  设置句柄
     * @param handle     定时器响应时，执行的句柄
     */
    void setHandle(const handler handle)
    {
        m_handler = handle;
    }

    /**
     * @brief setTicker 设置定时次数
     * @param tick      定时次数
     */
    void setTicker(int tick)
    {
        m_tick = tick;
    }

private:
    /**
     * @brief time_handle 定时器响应函数
     */
    void time_handle()
    {
        --m_tick;
        if (m_tick <= 0)
        {
            stop();
            return;
        }

        if (m_handler != NULL)
        {
            m_handler();
        }

        update();
    }

    /**
     * @brief update 更新定时器，实现重复响应效果
     */
    void update()
    {
        using namespace boost::posix_time;
        m_timer.expires_at(m_timer.expires_at() + milliseconds(m_millseconds));
        m_timer.async_wait(boost::bind(&Timer::time_handle, this));
    }

private:
    int m_millseconds;
    boost::asio::io_service m_service;
    boost::asio::deadline_timer m_timer;
    handler m_handler;
    int m_tick;
};

void print()
{
    cout << "hello timer" << endl;
}

int main()
{
    //async_timer();
    //timer();
    //timer_thread();

    Timer t;
    t.setHandle(&print);
    t.start();

    return 0;
}
