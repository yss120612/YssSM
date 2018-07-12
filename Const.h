// Const.h

#ifndef _CONST_h
#define _CONST_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

const uint8_t EX_PIN0 = 100;
const uint8_t EX_PIN1 = 101;
const uint8_t EX_PIN2 = 102;
const uint8_t EX_PIN3 = 103;
const uint8_t EX_PIN4 = 104;
const uint8_t EX_PIN5 = 105;
const uint8_t EX_PIN6 = 106;
const uint8_t EX_PIN7 = 107;

const uint8_t EX_PIN8 = 108;
const uint8_t EX_PIN9 = 109;
const uint8_t EX_PIN10 = 110;
const uint8_t EX_PIN11 = 111;
const uint8_t EX_PIN12 = 112;
const uint8_t EX_PIN13 = 113;
const uint8_t EX_PIN14 = 114;
const uint8_t EX_PIN15 = 115;

const uint8_t TEMPERATURE_PIN = D3;

const uint8_t ENC_A_PIN = D4;
const uint8_t ENC_B_PIN = D0;
const uint8_t ENC_BTN_PIN = D5;

const uint8_t EXT_CLC = D7;
const uint8_t EXT_LOCK = D6;
const uint8_t EXT_DATA = D8;

const uint8_t HEAT_NUL_PIN = D10;
const uint8_t HEAT_REL_PIN = EX_PIN15;
const uint8_t HEAT_DRV_PIN = D9;

const uint8_t TRIAC_COOL_PIN = EX_PIN2;

const uint8_t KRAN_OPEN_PIN = EX_PIN6;
const uint8_t KRAN_CLOSE_PIN = EX_PIN7;


const uint8_t  tkube[] = { 0x28, 0xFF, 0x73, 0x37, 0x67, 0x14, 0x02, 0x11 };
const uint8_t  tt1[] = { 0x28, 0xFF, 0x10, 0x5C, 0x50, 0x17, 0x04, 0x66 };
const uint8_t  tt2[] = { 0x28, 0xFF, 0xC1, 0x57, 0x50, 0x17, 0x04, 0x61 };
const uint8_t  tt3[] = { 0x28, 0xFF, 0x66, 0x5A, 0x50, 0x17, 0x04, 0x9E };
const uint8_t  tt4[] = { 0x28, 0xFF, 0xBC, 0x96, 0x50, 0x17, 0x04, 0x56 };
const uint8_t  tt5[] = { 0x28, 0xFF, 0x75, 0x98, 0x50, 0x17, 0x04, 0x92 };

#endif

