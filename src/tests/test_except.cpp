#include "util/Except.h"
#include <iostream>
#include <util/Logger.h>



int main()
{

    int my_id = 333;
    try {
        LOG_INFO("doing work..." << my_id);
        std::cout << "doing work..." << std::endl;
        throw_ex(std::runtime_error, "throwing runtime_error with id:" << my_id);
    }
    catch(const std::exception& e)
    {
        std::cout << "exception caught:" << e.what() << std::endl;
    }

    try {
        throw_ex(std::runtime_error, "throwing runtime_error with id:" << my_id);
    }
    catch(const std::runtime_error& e)
    {
        std::cout << "runtime exception caught:" << e.what() << std::endl;
    }
        return 0;
}
