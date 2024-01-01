# A compiler for Simple Language of Expressions

This project implements a compiler for the E++ language, which compiles E++ expressions into code that can run on a stack machine. The compiler supports features such as variable assignments, delete statements, return statements, and more.

## Introduction

Implemented a compiler for simple language mathematical expressions that proficiently generates commands tailored for a self-designed stack machine.

## Features

- Expression evaluation for the E++ language
- Variable assignments, delete statements, and return statements
- AVL tree implementation for symbol table
- Code generation for a stack machine

## Tools & Technologies

- AVL tree for efficient memory location storage of variables
- Minheap for managing available memory locations in the stack machine
- Stacks and vectors for creating an expression tree from expressions

## Project Structure

The project is structured into three main parts:

1. **Improving the Expression Evaluator:**
   - AVL tree implementation for symbol table
   - Helper functions for AVL tree rotations

2. **Code Generator:**
   - Implementation of a stack machine
   - Code generation for E++ expressions

3. **Bonus:**
   - Implementation of a min-heap for memory allocation optimization on stack mechine.

## Getting Started

To get started with the project, clone the repository to your local machine:

```
git clone 
cd eplusplus-compiler
```
### Building the compiler
Build the compiler using the provided Makefile:
```make```
This will generate the binary file in the `bin` directory.

### Running the Compiler
Compile E++ expressions from a file (e.g., samples/e++_correct.txt):
```./bin/e++ samples/e++_correct.txt```

This will generate the Targ code in the file targ.txt.

### Testing
To test the Targ syntax, use the provided Targ tester:
```./bin/tester```

Follow the instructions on the screen to run the tests.
## Contributing
If you find a bug or would like to contribute to the project, please ping me or Create a PR.<br>
_P.S.: If you find this stuff intersting please give a star to it :)_