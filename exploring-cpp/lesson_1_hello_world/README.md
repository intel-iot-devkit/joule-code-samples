## Lesson 1: Hello World

Hello world is one of the first programs anyone attempts to write in just about any programming language. You begin by including something called `iostream`. This library is the most commonly included file in most C++ programs, as it allows you to use certain functions for user input and feedback.

Next you enter the line, which makes the program use the namespace `std`. This means that the program will use the standard namespace. Although this is generally considered bad practice, it’s useful for beginners in order to help avoid simple mistakes.

Now we create our main function. This function is what is run by default, and can call other functions and classes at will. A function is basically a block of code that can generally be called from another block. It allows for things to be encapsulated, and minimizes the repetition of code. For now we’ll just be sticking with the main function, but in later examples we’ll generate more functions.

No you use `cout` in order to output something to the console. The double less-than signs “feed” cout, allowing you to specify exactly what it outputs. In this case, we are feeding it the string "Hello from Intel on Joule!”. The quotes, simply let the program know to display that as text, and ensures that it’s not a reference to something else. Now you use another pair of less-than signs to feed cout `endl` which simply moves the console curser to the next line.
Finally you enter the line `return 0;`which returns 0 to the program. This is needed at the end of your main function. This tells the program that the main function executed successfully. You can return non-zero at different points in the program in case something fails.

Now the program is complete, and you can attempt to compile it on your board. To do this, you will use “g++”. On your console in Joule enter the following command to compile your code.

`g++ lesson_1.cpp -o lesson_1`

This will compile the lesson_1.cpp file to an executable called lesson_1. The “-o” flag allows you to name an output file. Now, you can simply run the output file!

`./lesson_1`

### Troubleshooting

Running the program should show the string `Hello from Intel on Joule!` on the console.

If you get an error similar to `cout not declared in this scope` while compiling, be sure you properly included `iostream` as well as added the `using namespace std` and attempt to compile the program again.

### Tested
|	Operating System	|	Carrier Board	|	mraa Version	|
|:---------------------:|:-----------------:|:-----------------:|
|	Ostro 166			|	Intel Tuchuck	|	mraa 1.2.3		|
|	Ostro 166 			|	Intel Tuchuck	|	mraa 1.2.2		|