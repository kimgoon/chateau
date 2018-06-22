#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>


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
    std::thread th(&func, 100);
    std::thread th2(&func, 100);
    th.join();
    th2.join();
    std::cout << "value: " << v << std::endl;
    std::cout << "Outside thread:" << std::this_thread::get_id() << std::endl;

    return 0;
}
