# Minimal_Interpreter

Description:
This interpreter deals with a minimal form of a programming language. This form of said language only has one data type, integers, and has very few operators and functions as a result the capability of this language is very limited. The interpreter was designed using C++, this is because of how C++ handles strings and characters. C++ sees strings as an array of characters and not only that but it also allows strings to manipulated and interacted with as if it was a character array. These characteristics aided in creating a scanner that needs to accurately read in and classify the tokens as well as finding identifiers by being able to iterate through strings to find the appropriate characters.

Scanner:
Iteratates through a provided .jl file line by line and pulls individual tokens from the file. The individual tokens are then classified according to the opcodes shown in the keyword table. The identifiers and their respective values are also recorded seperately .This is then outputed to the console and written to a text file.

Parser:
The parser uses the tokens.txt file obtained from the scanner to verify the syntax of the .jl file. if there are no errors in the syntax then it will build and display a parse tree for illustrative purposes. The tree will also be written to a text file.

Interpreter:
This is the final program which will call on the scanner and parser to execute. If the scanner executes correctly and the parser finds no syntactical issues Then the interpreter will execute the program and output the result.
