# Navigating through the program in `gdb`

This example shows how to navigate through the program in `gdb`.
The following commands are used to navigate through a program to be debugged:
- `start`: This command is used to start the execution of the program to be debugged. It halts at the first line in the main function.
- `list`: This command does not change the execution state. It prints out lines of the source code surrounding the current line of the execution state.
- `next`: This command resumes the execution until the next line in the source code is reached. It steps over function calls.
- `step`: This command resumes the execution until the next line in the source code is reached. It steps into function calls. If a function is called during the resumption, this command halts at the first line of the called function.
- `break`: Does not change execution state. Sets a breakpoint at the desired position. Any other commands resuming execution will halt at set breakpoint, if execution passes over it.
- `continue`: Continues execution until a breakpoint is reached or an exception is thrown.

The example uses each of the commands at least once.
The accompanying `gdb.exe` (or `gdb.exe.in`) file contains comments on what how the demonstration navigates through the example program.
