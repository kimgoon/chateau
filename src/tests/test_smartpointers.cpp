#include <memory>
#include <string>
#include <iostream>

std::shared_ptr<std::string> word;


void foo()
{
    auto w = new std::string("hello");
    word.reset(w);
}


void bar()
{
    std::unique_ptr<std::string> w = std::make_unique<std::string>("i am temp");

    std::cout << __FUNCTION__ << ":" << *w << std::endl;
}

void pretty()
{
    std::cout << __FUNCTION__ << ":" << *word << std::endl;
}

int main(int argc, char** argv)
{
    foo();
    pretty();

    bar();
    return 0;
}
