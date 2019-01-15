#include <iostream>
#include <thread>
#include <chrono>

void f1(int n)
{
    for (int i = 0; i < n; ++i) {
        std::cout << "Thread 1: " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void f2(int& n)
{
    for (int i = 0; i < n; ++i) {
        std::cout << "Thread 2: " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    n ++;
}

int main()
{
    int n = 100;
    std::thread t1; // t1 is not a thread
    std::thread t2(f1, n); // pass by value
    std::thread t3(f2, std::ref(n)); // pass by reference
    std::thread t4(std::move(t3)); // t4 is now running f2(). t3 is no longer a thread
    std::thread t5(f2, std::ref(n)); // pass by reference
    t2.join();
    t4.join();
    t5.join();
    std::cout << "Finish!" << std::endl;
}
