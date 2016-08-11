#include <mraa.hpp>

class Relay {

public:
	Relay();
	Relay(int pin);
	~Relay();

	void on();
	void off();

	bool getState();

private:
	mraa::Gpio *outPin;

};