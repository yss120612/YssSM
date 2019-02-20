// 
// 
// 

#include "DallasTerm.h"


DallasTerm::DallasTerm(const uint8_t addr[], OneWire * d, float del)
{
	for (uint8_t i = 0; i < 8; i++) address[i] = addr[i];
	counter = 0;
	ds = d;
	delta = del;
	meajured = false;
	changed = false;
	temperature = 0;
	
}

float DallasTerm::getTemp() {
	/*if (changed)
	{
		float summ;
		for (uint8_t i = 0; i < dim; i++) {
			summ += temp[i];
		}
		temperature = summ / dim;
		changed = false;
	}*/
	return temperature;
}



void DallasTerm::process(long ms) {

	ds->reset(); //готовимся
	ds->select(address);
	
	float tm;
	if (meajured) {
	   ds->write(0xBE); // Просим передать нам значение регистров со значением температуры
		tm = (ds->read() | (ds->read() << 8)) * 0.0625 + delta;
		if (tm >= 0 && tm <= 110) {

			/*temp[counter] = tm;
			changed = true;
			counter = (counter < dim - 1) ? counter + 1 : 0;*/
			temperature = temperature * (1.0f - FILTER_K) + tm * FILTER_K;

		}
		meajured = false;
	}
	else {
		ds->write(0x44); // Даем датчику DS18b20 команду измерить температуру. Само значение температуры мы еще не получаем - датчик его положит во внутреннюю память
		meajured = true;
	}
	//lastWork = ms;
}

void DallasTerm::set12bit() {
	ds->reset(); // запрос шины 1-Wire
	ds->select(address); // выбор нашего DS18B20
	ds->write(0x4E); // запись в  scratchPad
	ds->write(0x00); // User byte 0 – Unused
	ds->write(0x00); // User byte 1 – Unused
	ds->write(0x7F); // выставляем 12 бит (0x7F)
}


