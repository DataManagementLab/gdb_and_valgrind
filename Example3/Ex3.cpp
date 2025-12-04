/*
 * Generated with Google Gemini
 *
 * Helgrind Complex Demonstration: Lock Order Violation (Deadlock)
 * * PURPOSE:
 * This program demonstrates a "Lock Inversion" or "Lock Order Violation".
 * It simulates a bank transfer where two threads transfer money between
 * two accounts in opposite directions.
 * * THE SCENARIO:
 * - Thread 1 transfers from Account A to Account B.
 * - Thread 2 transfers from Account B to Account A.
 * * THE BUG:
 * The locking logic is naive: it always locks the 'from' account first,
 * then the 'to' account. This creates a cycle:
 * Thread 1 holds Lock A, wants Lock B.
 * Thread 2 holds Lock B, wants Lock A.
 * * INSTRUCTIONS:
 * 1. Compile: g++ -g -pthread helgrind_deadlock.cpp -o helgrind_deadlock
 * 2. Run with Helgrind: valgrind --tool=helgrind ./helgrind_deadlock
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

struct Account {
    int id;
    int balance;
    std::mutex m;

    Account(int id, int bal) : id(id), balance(bal) {}
};

void transfer_unsafe(Account& from, Account& to, int amount) {
    // ---------------------------------------------------------
    // THE BUG IS HERE:
    // We lock the 'from' account first, then the 'to' account.
    // If two threads call this with opposite (from, to) pairs,
    // we get a lock order violation.
    // ---------------------------------------------------------

    // Lock the source account
    std::unique_lock<std::mutex> lock1(from.m);

    // We removed the sleep here.
    // Even without the sleep (which forces the deadlock),
    // Helgrind detects that we are acquiring locks in an inconsistent order.

    // Lock the destination account
    std::unique_lock<std::mutex> lock2(to.m);

    // Perform transfer
    if (from.balance >= amount) {
        from.balance -= amount;
        to.balance += amount;
        std::cout << "Transfer complete: " << from.id << " -> " << to.id << std::endl;
    }

    // Locks released automatically when lock1 and lock2 go out of scope
}

/* * A SAFE version of the function (for reference).
 * To fix the bug, we must always acquire locks in a consistent global order,
 * regardless of the direction of the transfer.
 */
void transfer_safe(Account& from, Account& to, int amount) {
    // Determine order based on unique ID (or memory address)
    std::mutex* first_mutex = &from.m;
    std::mutex* second_mutex = &to.m;

    if (from.id > to.id) {
        std::swap(first_mutex, second_mutex);
    }

    // Always lock the lower ID first
    std::unique_lock<std::mutex> lock1(*first_mutex);
    std::unique_lock<std::mutex> lock2(*second_mutex);

    // Perform transfer
    if (from.balance >= amount) {
        from.balance -= amount;
        to.balance += amount;
    }
}

int main() {
    Account acc1(1, 1000);
    Account acc2(2, 1000);

    std::cout << "[*] Starting transfer threads..." << std::endl;

    // Thread 1 moves money 1 -> 2
    std::thread t1([&]() {
        for (int i = 0; i < 50; ++i) { // Increased iterations to ensure Helgrind sees the pattern
            transfer_unsafe(acc1, acc2, 10);
        }
    });

    // Thread 2 moves money 2 -> 1
    std::thread t2([&]() {
        for (int i = 0; i < 50; ++i) {
            transfer_unsafe(acc2, acc1, 10);
        }
    });

    t1.join();
    t2.join();

    std::cout << "[*] Finished. Final balances: "
              << acc1.balance << ", " << acc2.balance << std::endl;

    return 0;
}
