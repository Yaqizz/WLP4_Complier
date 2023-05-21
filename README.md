# WLP4 Complier
## Introduction
The WLP4 Compiler is designed to process the WLP4 language, which is a simplified version of C. WLP4 includes essential programming constructs such as procedures, integers, pointers, arrays, arithmetic and boolean expressions, conditional statements, and loops.

## Features
**Scanning:** The compiler implements scanning using the Simplified Maximal Munch algorithm.    This algorithm ensures accurate tokenization of the source code by identifying the longest valid sequence of characters for each token.

**Parsing:** The compiler employs the SLR(1) parsing algorithm for parsing WLP4 programs. This algorithm analyzes the structure of the source code based on the defined grammar rules, ensuring syntactic correctness.

**Code Generation:** The compiler generates code from WLP4 to the MIPS assembly language, which is the instruction set architecture used by many processors. The code generation phase converts the high-level WLP4 code into low-level instructions that can be executed by the MIPS architecture.


For more information about the WLP4 language and its usage, refer to https://student.cs.uwaterloo.ca/~cs241/wlp4/WLP4tutorial.html.
