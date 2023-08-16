#include <iostream>
#include <thread>
#include <chrono>
#include "pewcesses/pewcesses.h"

using namespace ::std::chrono_literals;

void grand_child_func()
{
    ::std::cout << "grand_child" << ::std::endl;
    ::std::this_thread::sleep_for(10min);
    exit(0);
}

void child_func()
{
    ::std::cout << "child1" << ::std::endl;
    auto& p = pewcesses::fork(grand_child_func);
    ::std::this_thread::sleep_for(10min);
    p.wait();
}

int main(int argc, char** argv)
{
    auto& p = pewcesses::fork(child_func);
    ::std::this_thread::sleep_for(10min);
    p.wait();
    ::std::cout << p.status() << ::std::endl;
    return 0;
}
