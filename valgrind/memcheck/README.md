# Detecting memory related errors with memgrind
Memgrind lets you detect memoryrelated errors, such as memory leaks..
This subfolder contains multiple examples which contain various memory-related errors to demonstrate the use of helgrind.

### How to run the examples
Change to the subdirectory containing the example and `make demo`.

### buffer-overflow
In this example, we write a 41-character string to a 40-character buffer, leading to a buffer overflow.

### double-free
In this example, we free a freed pointer.

### fishy-args
Memgrind can check for **invalid memory (de-)allocation** function calls. In this example, we call malloc with a negative size.

### memory-leak
In this example we explore different memor-leak types which can be detected by memgrind.
The first type is definetly lost memory, which are memory regions, whose pointer values can no longer be referenced.
The second type is indirectly lost memory, which are memory regions, whose pointer values are stored in memory regions which themselves are lost (Loss of the head in a linked list for example).
The third type is possibly lost memory, which are memory regions where the compiler cannot determine, whether the region is lost or not.
This can happen for instance when incrementing pointers for iterating, where the original pointer could be restored when the amount of increments is known (see the example).
Still reachable memory regions are memory regions which are not lost, but were never deallocated correctly due to for eacmple a program crash.

### misalignment
In this example, we misalign a pointer to a 24-byte boundary, which is invalid, as it is not a power of 2.

### uninitialized-value
Memgrind can detect when an uninitialized value is used which may lead to unpredictable behaviour.

### use-after-free
Memgrind can detect memory usage of regioins which have been deallocated before.
