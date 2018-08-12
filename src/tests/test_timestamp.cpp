#include <iostream>
#include <time.h>

#include "util/StopWatch.h"


int main()
{
    struct timespec now;
    auto rc = clock_gettime(CLOCK_REALTIME, &now);


    auto res = util::StopWatch::get_res();
    std::cout << "sec:" << res.tv_sec << std::endl;
    std::cout << "nsec:" << res.tv_nsec << std::endl;


    char buf[28];


    std::cout << "sec:" << now.tv_sec << std::endl;
    std::cout << "nsec:" << now.tv_nsec << std::endl;

    struct tm sec;
    localtime_r(&(now.tv_sec), &sec);
    auto ret = strftime(buf, sizeof(buf), "%F_%T", &sec);

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

/*
YYYY-MM-DD_HH:MM:SS.mmmnnn
*/
std::cout << buf << std::endl;

    return 0;
}
