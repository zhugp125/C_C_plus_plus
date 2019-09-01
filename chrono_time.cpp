#include <iostream>
#include <chrono>
#include <string>

using namespace std;

// g++ chrono_time.cpp -std=c++11

std::string getCurrentTime()
{
    using namespace std::chrono;
    auto tt = system_clock::to_time_t(system_clock::now());
    tm* p_tm = localtime(&tt);
    char date[60];
    sprintf(date, "%d/%02d/%02d %02d::%02d::%02d",
            p_tm->tm_year + 1900, p_tm->tm_mon + 1, p_tm->tm_mday,
            p_tm->tm_hour, p_tm->tm_min, p_tm->tm_sec);
    return std::string(date);
}

int main()
{
    /**
     * 1. 时间段 duration
     * 定义：
     * template <class Rep, class Period> class duration
     * Rep 数值类型(int,long,long long)
     * Period ratio类型，表示时间单位
     *
     * 已经定义过的时间类型
     * typedef duration<long long,         nano> nanoseconds;   纳秒
     * typedef duration<long long,        micro> microseconds;  微秒
     * typedef duration<long long,        milli> milliseconds;  毫秒
     * typedef duration<long long              > seconds;       秒
     * typedef duration<     long, ratio<  60> > minutes;       分
     * typedef duration<     long, ratio<3600> > hours;         时
     *
     * 时间段转换
     * template <class _ToDuration, class _Rep, class _Period> duration_cast(const duration<_Rep, _Period>& __fd)
     *
     * 成员函数
     * count()  ->  Rep
     * max()    ->  duration
     * min()    ->  duration
     * zone()   ->  duration
     */
    std::chrono::hours h(1);
    std::cout << h.count() << " hour" << std::endl;
    std::chrono::minutes m(60);
    std::cout << m.count() << " minutes" << std::endl;
    assert(std::chrono::duration_cast<std::chrono::hours>(m) == m);

    /**
     * 2. 时间点 time_point
     * 定义：
     * time_point 表示一个具体的时间
     * template <class _Clock, class _Duration = typename _Clock::duration> class time_point
     * Clock 计时
     * Duration 时间单位
     *
     * 已经定义过的时间点
     * std::chrono::system_clock::time_point
     * std::chrono::steady_clock::time_point
     * std::chrono::high_resolution_clock::time_point
     *
     * 时间点转换
     * template <class _ToDuration, class _Clock, class _Duration> time_point_cast(const time_point<_Clock, _Duration>& __t)
     */
    std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> tp(std::chrono::hours(1));
    std::cout << "since epoch " << tp.time_since_epoch().count() << " second" << std::endl;

    auto stp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(tp);
    std::cout << "since epoch " << stp.time_since_epoch().count() << " microsecond" << std::endl;

    /**
     * 3. 时钟 clock
     * 定义：
     * std::chrono::system_clock             系统时钟
     * std::chrono::steady_clock             稳定的时钟，不随系统时钟变化而变化
     * std::chrono::high_resolution_clock    高精度时钟
     *
     * 方法
     * now()         -> time_point
     * to_time_t()   -> time_t
     * from_time_t() -> time_point
     */
    auto now_tp = std::chrono::system_clock::now();
    std::cout << "now time : " << now_tp.time_since_epoch().count() << std::endl;

    std::cout << getCurrentTime() << std::endl;

    cout << "Hello World!" << endl;
    return 0;
}
