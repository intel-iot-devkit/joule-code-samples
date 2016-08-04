//Truly learn to code with Intel on Grosse Tete

#include <iostream> //The most commonly-included file. This allows you to use cin and cout to print to the console and collect user input.

using namespace std; //Commonly considered bad practice, this command prevents some simple mistakes that can be difficult to track down for a beginner. Generally, though, you wouldn't do this.

//The main entry point for your program. This is the function that the OS (OSTRO) calls when it "runs" your code.
//This should always follow one of three formats. Those are, in order of commonality:
//-		int main() {}
//-		int main(int argc, char *argv[]) {}
//-		int main(int argc, char **argv) {}
int main(int argc, char **argv) {
	cout << "Hello from Intel on Grosse Tete!" << endl; 	// This line should print to the console.
	return 0; 												//Do not forget this line. You should always return 0 if your code ran successfully, and non-zero of an error was caught during execution.
}