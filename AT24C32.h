// AT24C32.h

#ifndef _AT24C32_h
#define _AT24C32_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <Wire.h>
const uint8_t  AT24C32_ADDRESS = 0x57;
const uint8_t  EEPROM_PAGE_SIZE = 32;
const uint8_t  EEPROM_WORK_SIZE = EEPROM_PAGE_SIZE / 2;
const uint32_t EEPROM_WRITE_TIMEOUT = 10;

class AT24C32 {
public:
	

	void init(bool fast = false);
	void init(int8_t pinSDA, int8_t pinSCL, bool fast = false);
	bool begin(uint8_t address = AT24C32_ADDRESS);
	uint8_t read(uint16_t index);
	void read(uint16_t index, uint8_t* buf, uint16_t len);
	void write(uint16_t index, uint8_t data);
	void write(uint16_t index, const uint8_t* buf, uint16_t len);
	template<typename T> T & get(uint16_t index, T& t) {
		read(index, (uint8_t*)&t, sizeof(T));
		return t;
	}
	template<typename T> const T& put(uint16_t index, const T& t) {
		write(index, (const uint8_t*)&t, sizeof(T));
		return t;
	}

private:
	uint8_t _address;
};


//extern AT24C32 at24c32;

#endif

