// Const.h

#ifndef _CONST_h
#define _CONST_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#define ENCODER_LOG1
#define _SERIAL1


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


const uint8_t MP_PIN0 = EX_PIN8;
const uint8_t MP_PIN1 = EX_PIN9;
const uint8_t MP_PIN2 = EX_PIN1;
const uint8_t MP_PIN3 = EX_PIN10;

const uint8_t WS1_PIN= 0;
const uint8_t WS1_PWR_PIN = EX_PIN2;

const uint8_t WS2_PIN = 1;
const uint8_t WS2_PWR_PIN = EX_PIN3;

const uint8_t TEMPERATURE_PIN = D3;

const uint8_t ENC_A_PIN = D4;
const uint8_t ENC_B_PIN = D0;
const uint8_t ENC_BTN_PIN = D5;

const uint8_t EXT_CLC = D7;
const uint8_t EXT_LOCK = D6;
const uint8_t EXT_DATA = D8;

const uint8_t HEAT_NUL_PIN = D7;
const uint8_t HEAT_REL_PIN = EX_PIN6;
const uint8_t HEAT_DRV_PIN = D6;

const uint8_t TRIAC_COOL_PIN = EX_PIN5;

const uint8_t KRAN_OPEN_PIN = EX_PIN7;
const uint8_t KRAN_CLOSE_PIN = EX_PIN15;


const uint8_t term_addr [][8]={
	{ 0x28, 0xFF, 0x73, 0x37, 0x67, 0x14, 0x02, 0x11 },//in Cube sensor
	{ 0x28, 0xFF, 0x36, 0x1E, 0xC0, 0x17, 0x02, 0x10 },//in capsule tsarga
	{ 0x28, 0xFF, 0x10, 0x5C, 0x50, 0x17, 0x04, 0x66 },//TSA
	{ 0x28, 0xFF, 0x75, 0x98, 0x50, 0x17, 0x04, 0x92 },//TRIAK RADIATOR
	{ 0x28, 0xFF, 0xC1, 0x57, 0x50, 0x17, 0x04, 0x61 },//2
	{ 0x28, 0xFF, 0x66, 0x5A, 0x50, 0x17, 0x04, 0x9E },//3
	{ 0x28, 0xFF, 0xBC, 0x96, 0x50, 0x17, 0x04, 0x56 }//4
	
};


const char hex[]{ '0','1','2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C','D','E','F' };

enum taddr{
	T_KUBE,
	T_TSARGA,
	T_TSA,
	T_TRIAK,
	T_WATER,
	T_DEF
};

//const uint8_t  tkube[] = { 0x28, 0xFF, 0x73, 0x37, 0x67, 0x14, 0x02, 0x11 };
//const uint8_t  tt1[] = { 0x28, 0xFF, 0x10, 0x5C, 0x50, 0x17, 0x04, 0x66 };
//const uint8_t  tt2[] = { 0x28, 0xFF, 0xC1, 0x57, 0x50, 0x17, 0x04, 0x61 };
//const uint8_t  tt3[] = { 0x28, 0xFF, 0x66, 0x5A, 0x50, 0x17, 0x04, 0x9E };
//const uint8_t  tt4[] = { 0x28, 0xFF, 0xBC, 0x96, 0x50, 0x17, 0x04, 0x56 };
//const uint8_t  tt5[] = { 0x28, 0xFF, 0x75, 0x98, 0x50, 0x17, 0x04, 0x92 };

const uint8_t  AT24C32_ADDRESS = 0x57;
const uint8_t  EEPROM_PAGE_SIZE = 32;
const uint8_t  EEPROM_WORK_SIZE = EEPROM_PAGE_SIZE / 2;
const uint32_t EEPROM_WRITE_TIMEOUT = 10;

const uint16_t RTC_MEM_SIZE = 512;

enum mo{
	MODE_MAIN,
	MODE_SUVID,
	MODE_DISTILL,
	MODE_RECTIFY
};

enum mydata {
	DS_TKUBE,
	DS_TTSA,
	DS_TTSARGA,
	DS_TTRIAK,
	DS_HPOWER,
	DS_KRANSTATE,
	DS_DISTSTART,
	DS_DISTSTATE,
	DS_DISTEND,
	DS_RECTSTART,
	DS_RECTSTATE,
	DS_RECTSTOP,
	DS_RECTEND,
	DS_SUVIDSTART,
	DS_SUVIDSTATE,
	DS_SUVIDTIMELEFT,
	DS_SUVIDTARGET,
	DS_SUVIDEND
};


#define PROC_OFF  0 //начало
#define PROC_FORSAJ  1 //разгон до temp_start
#define PROC_WORK 2
#define PROC_GET_HEAD 3
#define PROC_SELF_WORK 4

#define PROCEND_NO 0 //работаем
#define PROCEND_TIME 1 //закончили по времени
#define PROCEND_ERROR 2 //закончили с ошибкой
#define PROCEND_FAULT 3 //закончили аварийно
#define PROCEND_TEMPERATURE 4 //закончили по температуре
#define PROCEND_MANUAL 5 //закончили вручную

#define PROCERR_OK 0 //нет ошибок
#define PROCERR_NOTKUB 1 //нет градусника в кубе
#define PROCERR_NOHEATER 2 //нет тена

const uint16_t test_time = 10000;//5 секунд

const long checkTSA = 1000 * 60 * 3;//через 3 минуты проверяем TSA после коррекции

#endif

