#pragma once

#include <iostream>
#include <chrono>
#include <ctime>
#include <time.h>

inline static const char* get_formatted_time(char* buf)
{
    struct timespec now;
    //auto rc = clock_gettime(CLOCK_REALTIME, &now);
    clock_gettime(CLOCK_REALTIME, &now);
    struct tm sec;
    localtime_r(&(now.tv_sec), &sec);
    //auto ret = strftime(buf, 28, "%F_%T", &sec);
    strftime(buf, 28, "%F_%T", &sec);
    int usec = now.tv_nsec / 1000;
    buf[26] = '\0';
    buf[25] = (usec % 10) + '0';
    usec /= 10;
    buf[24] = (usec % 10) + '0';
    usec /= 10;
    buf[23] = (usec % 10) + '0';
    usec /= 10;
    buf[22] = (usec % 10) + '0';
    usec /= 10;
    buf[21] = (usec % 10) + '0';
    usec /= 10;
    buf[20] = (usec % 10) + '0';
    buf[19] = '.';
    return buf;
}

#define LOG_FATAL(msg) {        \
    char buf[27];               \
    get_formatted_time(buf);    \
    std::cout << buf << " [FATAL] " << msg << std::endl; \
}

#define LOG_ERROR(msg) {        \
    char buf[27];               \
    get_formatted_time(buf);    \
    std::cout << buf << " [ERROR] " << msg << std::endl; \
}

#define LOG_WARN(msg) {         \
    char buf[27];               \
    get_formatted_time(buf);    \
    std::cout << buf << " [INFO] " << msg << std::endl; \
}

#define LOG_INFO(msg) {         \
    char buf[27];               \
    get_formatted_time(buf);    \
    std::cout << buf << " [INFO] " << msg << std::endl; \
}

#define LOG_DEBUG(msg) {        \
    char buf[27];               \
    get_formatted_time(buf);    \
    std::cout << buf << " [DEBUG] " << msg << std::endl; \
}

