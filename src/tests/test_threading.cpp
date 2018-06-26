#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>
#include <chrono>

#include "util/StopWatch.h"

std::mutex myLock;

int v = 0;

void func(int x)
{
    std::lock_guard<std::mutex> guard(myLock);
    v += 1;
    std::cout << __FUNCTION__ << ":" << std::this_thread::get_id() << ":" << x << std::endl;
}


int main()
{
    util::StopWatch sw(true);
    std::thread th(&func, 100);
    std::thread th2(&func, 100);
    th.join();
    th2.join();
    std::cout << "value: " << v << std::endl;
    std::cout << "Outside thread:" << std::this_thread::get_id() << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));
    sw.stop_time();

    std::cout << "Elapsed:" << sw.get_elapsed() << std::endl;
    std::cout << "Elapsed:" << sw.get_elapsed_as_str() << std::endl;
    auto ts = util::StopWatch::get_res();
    std::cout << "Res:" << ts.tv_sec << "." << ts.tv_nsec << std::endl;
    return 0;
}
