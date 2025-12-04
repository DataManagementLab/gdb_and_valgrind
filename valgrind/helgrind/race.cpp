//============================================================================
// Name        : CyclicDependencyDeadLock.cpp
// Author      : Som
// Version     :
// Copyright   : som-itsolutions
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <thread>
#include <mutex>


std::mutex lock1, lock2;

void threadA() {
    int count = 0;
    std::lock_guard<std::mutex> guard1(lock1);
    for (int i = 0; i < 100000; i++) {
        count += rand();
    }
    std::lock_guard<std::mutex> guard2(lock2);
}

void threadB() {
    std::lock_guard<std::mutex> guard2(lock2);
    int count = 0;
    for (int i = 0; i < 100000; i++) {
        count += rand();
    }
    std::lock_guard<std::mutex> guard1(lock1);
}

int main() {
    std::thread t1(threadA);
    std::thread t2(threadB);

    t1.join();
    t2.join();

    return 0;
}
