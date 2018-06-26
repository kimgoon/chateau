#pragma once

#include <time.h>
#include <stdexcept>
#include <cstring>
#include <string>

namespace util {

// StopWatch header only utility class to measure time elapsed using the wall clock
class StopWatch {
public:
    // ctor, optionally start the stopwatch
    inline StopWatch(bool start) {
        if (start) {
            start_time();
        }
    }
    // start_time starts the stop watch
    inline void start_time()
    {
        auto rc = clock_gettime(CLOCK_REALTIME, &m_start);
        if (rc != 0) {
            throw std::runtime_error("clock_gettime returned rc:" + std::string(strerror(errno)));
        }
    }

    // stops the stop watch and sets elapsed
    inline void stop_time()
    {
        struct timespec end;
        auto rc = clock_gettime(CLOCK_REALTIME, &end);
        if (rc != 0) {
            throw std::runtime_error("clock_gettime returned rc:" + std::string(strerror(errno)));
        }
        m_elapsed = get_diff(&end, &m_start);
    }

    // get_elapsed returns the calculcated elapsed time
    inline const int64_t get_elapsed() {
        return m_elapsed;
    }

    // get_elapsed_as_str returns the calculated elapsed time as string, where the .
    // separates seconds and nanos
    inline const std::string get_elapsed_as_str() {
        char buf[10];
        sprintf(buf, "%09lld", m_elapsed% NS_PER_S);
        std::string res;
        res += std::to_string(m_elapsed / NS_PER_S) +"."+ buf;
        return res;
    }

    inline static struct timespec get_res() {
        struct timespec ts;
        clock_getres(CLOCK_REALTIME, &ts);
        return ts;
    }

private:
    inline int64_t get_diff(const struct timespec* end, const struct timespec* begin)
    {
        uint64_t end_time = end->tv_sec * NS_PER_S + end->tv_nsec;
        uint64_t begin_time = begin->tv_sec * NS_PER_S + begin->tv_nsec;
        return end_time - begin_time;
    }

    static constexpr uint32_t NS_PER_S = 1000000000;
    struct timespec m_start;
    int64_t m_elapsed;
};

} // close namespace util
