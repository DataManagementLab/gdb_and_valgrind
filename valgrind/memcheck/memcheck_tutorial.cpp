/*
 * Generated with Google Gemini
 *
 * Valgrind Memcheck Demonstration Program
 * * PURPOSE:
 * This program intentionally contains three common memory errors:
 * 1. Using an uninitialized variable.
 * 2. Illegal write (buffer overflow).
 * 3. A memory leak (forgetting to free allocated memory).
 * * INSTRUCTIONS:
 * 1. Compile: g++ -g memcheck_errors.cpp -o memcheck_demo
 * 2. Run with Memcheck: valgrind --tool=memcheck --leak-check=full ./memcheck_demo
 */

#include <iostream>
#include <cstdlib>

// 1. Error: Use of Uninitialized Value
void use_uninitialized_value() {
    std::cout << "--- Function 1: Uninitialized Value ---\n";
    int* data = new int[10];

    // We intentionally only initialize the first element
    data[0] = 5;

    // Memcheck will flag this line because data[1] has an unknown state.
    int sum = data[0] + data[1];
    bool sum_even = sum & 1;

    std::cout << "Is result even? " << sum_even << "\n";
    delete[] data;
}

// 2. Error: Illegal Write (Buffer Overflow)
void illegal_memory_access() {
    std::cout << "\n--- Function 2: Illegal Access ---\n";

    // Allocate space for 5 integers
    int* buffer = new int[5];

    // Helgrind will flag this line as an illegal write, because
    // the allocated indices are 0 through 4. Index 5 is out of bounds.
    buffer[5] = 99;

    std::cout << "Attempted write outside of allocated memory (Buffer Overflow).\n";
    delete[] buffer;
}

// 3. Error: Memory Leak
void memory_leak() {
    std::cout << "\n--- Function 3: Memory Leak ---\n";

    // Allocate 100 bytes on the heap
    char* big_block = new char[100];

    size_t ptr = 0;
    ptr = 5;
    *(size_t*) ptr = 0;

    // We intentionally forget to call 'delete[] big_block;'
    // Memcheck will report 100 bytes definitely lost at the end of execution.
    std::cout << "100 bytes allocated but not freed (Memory Leak).\n";
}

int main() {
    std::cout << "Starting Memcheck Demo...\n";

    use_uninitialized_value();
    illegal_memory_access();
    memory_leak();

    std::cout << "\nMemcheck Demo finished. Now run with Valgrind!\n";
    return 0;
}
