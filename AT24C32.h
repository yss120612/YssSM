// AT24C32.h

#ifndef _AT24C32_h
#define _AT24C32_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class AT24C32 {
public:
	static const uint8_t AT24C32_ADDRESS = 0x57;

	static void init(bool fast = false);
	static void init(int8_t pinSDA, int8_t pinSCL, bool fast = false);
	static bool begin(uint8_t address = AT24C32_ADDRESS);
	static uint8_t read(uint16_t index);
	static void read(uint16_t index, uint8_t* buf, uint16_t len);
	static void write(uint16_t index, uint8_t data);
	static void write(uint16_t index, const uint8_t* buf, uint16_t len);
	template<typename T> static T & get(uint16_t index, T& t) {
		read(index, (uint8_t*)&t, sizeof(T));
		return t;
	}
	template<typename T> static const T& put(uint16_t index, const T& t) {
		write(index, (const uint8_t*)&t, sizeof(T));
		return t;
	}

private:
	static uint8_t _address;
};


extern AT24C32 at24c32;

#endif

