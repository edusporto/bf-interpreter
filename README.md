# bf-interpreter
Interpreter for the "Brainfuck" language written in C++

## About
This program assumes blocks of memory of 8 bits each. In the future, support for multiple 
memory block sizes may be added.

## Building
This program does not require any external dependencies.
You can build it using your favorite C++ compiler.
Example:
``` g++ bfinterpreter.cpp -o bfinterpreter.out ```

## Usage
After building the program, you need to specify two arguments to the executable:
* The number (in bytes) of memory to be allocated
* The path to a file containing BF (Brainfuck) code

Example:
``` ./bf-interpreter.out 100 program.bf ```

A file containing an example Hello World is included in the repository.
