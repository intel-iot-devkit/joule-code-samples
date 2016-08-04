#ifndef RELAY_H_
#define RELAY_H_

#include <mraa.hpp>

class Relay {
public:
	Relay(int pin);
	~Relay();
	void on();
	void off();
	bool getState();
private:
	mraa::gpio *relay;
};

#endif