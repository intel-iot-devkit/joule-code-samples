#define LCD_ADDR (0x3E)
#define RGB_ADDR (0x62)
#define ADC_ADDR (0x50)

#include "relay.h"
#include "jhd1313m1.hpp"
#include "adc121c021.hpp"
#include <sstream>
#include <string>
#include <iomanip>

class Devices {
private:
	Jhd1313m1 *lcd;
	ADC121C021 *adc;
	Relay *ac;
	Relay *htr;
public:
	//Default (empty) constructor.
	Devices();
	//Constructor
	Devices(unsigned int lcd = LCD_ADDR, unsigned int rgb = RGB_ADDR, unsigned int adc = ADC_ADDR, int acPin, int htrPin);
	//Destructor
	~Devices();

	//Functions

	template <typename T> string stringify(T data);
	template <> string stringify(float data);

	void display(int row, int col, string str);
	void clear();
	void color(int r, int g, int b);
	float getTemp();
}