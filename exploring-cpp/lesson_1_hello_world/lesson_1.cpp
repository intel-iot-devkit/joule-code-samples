/*
Copyright (c) 2015 - 2016 Intel Corporation.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

//Exploring C++ Programming on the Intel Joule Module

#include <iostream> //The most commonly-included file. This allows you to use cin and cout to print to the console and collect user input.

using namespace std; //Commonly considered bad practice, this command prevents some simple mistakes that can be difficult to track down for a beginner. Generally, though, you wouldn't do this.

//The main entry point for your program. This is the function that the OS (OSTRO) calls when it "runs" your code.
//This should always follow one of three formats. Those are, in order of commonality:
//-		int main() {}
//-		int main(int argc, char *argv[]) {}
//-		int main(int argc, char **argv) {}
int main(int argc, char **argv) {
	cout << "Hello from Intel on Joule!" << endl; 	// This line should print to the console.
	return 0; 												//Do not forget this line. You should always return 0 if your code ran successfully, and non-zero of an error was caught during execution.
}