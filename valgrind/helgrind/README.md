# Detecting thread related errors with Helgrind
Helgrind lets you detect thread related errors, such as race conditions.
This subfolder contains three examples which contain various thread-related errors to demonstrate the use of helgrind.

### How to run the examples
Change to the subdirectory containing the example and `make demo`.

### invalid-lock-ops
This example demonstrates Helgrind's lock/mutex verification capabilities.
Locks are errorneously used, for example, an unlocked lock is unlocked or a lock is never released after locking.

### lock-order
This example demonstrates Helgrind's deadlock detection capabilities.
In this example, two threads are trying to lock two locks in reverse order to each other, leading to a potential deadlock.

### race
This example demonstrates Helgrind's race condition detection.
Hereby two threads try to write to the same location without any synchronization, leading to a possible race condition.
