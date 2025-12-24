# GDB tutorials
This subfolder of the repository contains a tutorial on how to use `gdb`.

## Structure of the tutorials
Each tutorial contains a C++ program, a `Makefile`, a `README` and a `gdb.exe` file.
The Makefile contains targets to build the program as well as execute the demonstration of the `gdb` tutorial.
The `README` briefly explains the goal of the tutorials.
The `gdb.exe` contains the gdb commands to demonstrate the tutorial.
It is annotated with print and echo commands that format the output of the script to emulate, how it would look like when the executed in `gdb` manually.
The `gdb.exe.in` file contains the same content, but without the annotations.

## Executing the tutorials
The tutorials can be executed directly with the `Makefile`.
To build the program, simply execute `make`.
If you want to execute the demonstration, execute `make demo`.
