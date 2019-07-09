# bf-interpreter
Interpreter for the "Brainf*ck" language written in C++

## About
This program assumes blocks of memory of 8 bits each. In the future, support for multiple 
memory block sizes may be added.

## Building
This program does not require any external dependencies.  
You can build it using your favorite C++ compiler.  
Example:  
```g++ bfinterpreter.cpp -O3 -o bfinterpreter.out```  
The O3 argument optimizes the program, so it runs faster and the file size gets smaller.  

## Usage
After building the program, you can specify two arguments to the executable:
* (REQUIRED) The path to a file containing BF (Brainfuck) code
* (OPTIONAL) The amount (in bytes) of memory to be allocated
  
Example:  
```./bfinterpreter.out program.bf    # allocates the default of 30000 bytes of memory```  
```./bfinterpreter.out program.bf 50 # allocates 50 bytes of memory```  

A file containing an example Hello World is included in the repository.
