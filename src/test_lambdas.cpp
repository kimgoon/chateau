#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>


void foo(std::function<void(int)> f)
{
    f(12);

}

void* operator new(std::size_t n) {
    std::cout << "Allocating " << n << " bytes" << std::endl;
    return malloc(n);
}

int main(int argc, char** argv)
{
    // [ capture clause] (params) -> return type { definition }
    int some_val = 0;
    auto filter = [&](int v) {
        std::cout << "print:" << v << std::endl;
        some_val = 122222;
    };

    foo(filter);

    std::cout << "type:" << typeid(filter).name() << std::endl;

    const int thres = 2;

    filter(23);

    filter(32);

    std::vector<int> numbers { 1, 2,3, 8, 9, 10};
    auto large = std::count_if(numbers.begin(), numbers.end(), [] (const int& v) -> bool { return v > 5; });



    std::cout << "size of: " << large << std::endl;

    auto large2 = std::find_if(numbers.begin(), numbers.end(), [] (const int& v) { return v > thres; });


    while(large2 != numbers.end()) {
        std::cout << "s:" << *large2 << std::endl;
        large2++;
    }

    std::cout << "size of: " << large << std::endl;
    std::cout << "size of: " << some_val << std::endl;


    {
        std::vector<int> nums = {0,1,2,3,4,5,6,7,8};
        auto f = std::lower_bound(nums.begin(), nums.end(), 5);
        std::cout << "lower_bound(.., 10):" << *f << std::endl;
        auto s = std::upper_bound(nums.begin(), nums.end(), 5);
        std::cout << "upper_bound(.., 10):" << *s << std::endl;

    }











    return 0;
}
