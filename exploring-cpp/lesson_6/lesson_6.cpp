//Exploring C++ Programming on the Intel Joule Module

/*
* Now, let's try something new. For this lesson, you won't need a circuit at all;
* you'll just need your Grosse Tete board, and your laptop to make a serial terminal
* connection to it. Let's get started!
*
* First, we'll need to get a copy of cmake. Use the following commands to install
* cmake.
*
* cd
* git clone https://github.com/Kitware/CMake
* cd CMake
* ./bootstrap && make && make install
* cd
* 
* Now that cmake is installed, we need to download a copy of the source for Crow. To
* do this, use the following commands.
*
* cd
* git clone https://github.com/ipkn/crow
* cd crow
* mkdir build
* cd build
* cmake ..
* make
* cd amalgamate
* cp crow_all.h /usr/include/
* cd
*
* Now, you're ready to get started on our little adventure.
* Compile with the flags -lboost_system and -pthread
*/

#include <crow_all.h>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv) {

	//Crow is a web microframework that allows you to serve
	//small, simple webpages from within a c++ program. You
	//can define completely custom routes, and any type of
	//basic page can be defined. So let's define a simple
	//web page!

	crow::SimpleApp app;

	//That's the actual server instance, ready to be loaded
	//with routes and information. So let's go ahead and load
	//something up. Included in the lessons directory is an
	//html file called "lesson_6_index.html". We'll use that
	//for this lesson. Let's go ahead and route it in.

	CROW_ROUTE(app, "/")([](){
		crow::mustache::context ctx;
		return crow::mustache::load("lesson_6_index.html").render();
	});

	app.port(80).run();

	return 0;
}

/*
* How easy was that? Easy, right? You now have a tiny, simple webserver
* that you can then use to get data from users. In the next lesson, we'll
* put that to use.
*/