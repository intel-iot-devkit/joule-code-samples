## Lesson 6: Using Crow

This lesson is focused on creating a small webserver using the Crow micro-framework for web. Ensure that you’ve opened your IP tables in order to access the server!

#### The Code

In this lesson you won't need a circuit at all, but if you're planning on continuing it would be fine to leave your circuit from lesson 5 together for the moment. This lesson will be focusing on Crow, a lightweight micro-framework for displaying HTML webpages. We can use it to retrieve feedback outside of the console, in order to allow the board to do what you need it to remotely. In order to build applications using Crow you need to install it. So let's get to it!

#### Installing Crow

In order to build Crow, we need to install Cmake. Make sure you have an internet connection before you get started. Go ahead and enter the following commands to get Cmake installed.

```bash
cd
git clone https://github.com/Kitware/CMake
cd CMake
./bootstrap && make && make install
```

This should install Cmake for you and allow you to install anything that uses Cmake! Now we just need to install Crow. Use the following commands to do so.

```bash
cd
git clone https://github.com/ipkn/crow
cd crow
mkdir build
cd build
cmake ..
make
cd amalgamate
cp crow_all.h /usr/include/
cd
```

Now let's get to the code!

#### The Code

We begin by including `crow_all.h` which allows us to use the Crow functions and server. In order to start the server we call `crow::SimpleApp app;`. That's the actual server, ready to be loaded with all sorts of information to customize the server for your needs. We'll be using the file `lesson_6_index.html`. The following block of code does several things, so let's take a look at it.

```cpp
	CROW_ROUTE(app, "/")([](){
		crow::mustache::context ctx;
		return crow::mustache::load("lesson_6_index.html").render();
	});
```

As convoluted as this seems, it simply builds up the server, using the file `lesson_6_index.html`. This means we're ready to start the server. We do so by simply saying `app.port(80).run();`. The server will now be up and running! 

Now ensure to use the proper compiler flags when you attempt to compile this program!

`g++ -lpthread -lboost_system lesson_6.cpp -o lesson_6`

Once you've compiled the program, you'll need to get your boards IP address. The device you want to use to access the web server will need to be on the same network as your board. To look up your IP address, use the `ifconfig` command. Now you can start up the program, which will start the Crow server. Connect to it by typing in the IP address you got from your `ifconfig` command, and you should see the HTML page!

#### Troubleshooting

If you have any issues with the program compiling, ensure that your compiler flags are correct.

If you can't access your webserver there are a few problems that can generally happen. First, you must make sure that your device is on the same network as your board. Finally, ensure that your board's ports are correctly opened. Do so by running the following code.

```bash
iptables -F
iptables -P INPUT ACCEPT
iptables -P OUTPUT ACCEPT
iptables -P FORWARD ACCEPT
iptables -S
```

This should set everything up properly.