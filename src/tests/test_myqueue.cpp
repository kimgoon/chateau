#include "fastqueue.h"

#include <iostream>
#include <atomic>



const uint32_t MAX_VALUE = 5;

std::atomic<uint32_t> g_counter;

void init()
{
    g_counter = 0;
}


void add()
{
    auto v = g_counter.load(std::memory_order_acquire);
    if (v < MAX_VALUE) {
        g_counter.fetch_add(1, std::memory_order_relaxed);
    }
    else {
        std::cout << "max hit" << std::endl;
    }
}

void remove()
{
    auto v = g_counter.load(std::memory_order_acquire);
    if (v <= 0) {
        std::cout << "empty" << std::endl;
    }
    else {
        g_counter.fetch_sub(1, std::memory_order_relaxed);
    }
}


struct MyData {
    int m_v;
};


void my_test()
{
    FastQueueSPSC<MyData> fq;

    fq.push(new MyData());

    std::cout << "size:" << fq.size() << std::endl;


}


int main(int argc, char** argv)
{
    std::cout << __FUNCTION__ << ":hello" << std::endl;

    init();
    for (int i = 0; i < 6; i++)
    {
        add();
    }
    for (int i = 0; i < 6; i++)
    {
        remove();
    }

    std::cout << "counter:" << g_counter.load(std::memory_order_relaxed) << std::endl;
    
    my_test();
    return 0;
}
