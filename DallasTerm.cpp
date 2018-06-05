// 
// 
// 

#include "DallasTerm.h"


float DallasTerm::getTemp() {
	float summ;
	for (uint8_t i = 0; i < dim; i++) {
		summ += temp[i];
	}
	return summ / dim;
}

void DallasTerm::process(uint16_t ms) {
//	if (ms - lastWork < interval) return;

	ds->reset(); // ������ ���������
	ds->select(address);

	if (meajured) {
	   ds->write(0xBE); // ������ �������� ��� �������� ��������� �� ��������� �����������
       temp[counter]= (ds->read() | (ds->read()<<8)) * 0.0625+delta;
	   counter = (counter < dim - 1) ? counter + 1:0;
	   meajured = false;
	}
	else {
		ds->write(0x44); // ���� ������� DS18b20 ������� �������� �����������. ���� �������� ����������� �� ��� �� �������� - ������ ��� ������� �� ���������� ������
		meajured = true;
	}
	//lastWork = ms;
}

void DallasTerm::set12bit() {
	ds->reset(); // ������ ���� 1-Wire
	ds->select(address); // ����� ������ DS18B20
	ds->write(0x4E); // ������ �  scratchPad
	ds->write(0x00); // User byte 0 � Unused
	ds->write(0x00); // User byte 1 � Unused
	ds->write(0x7F); // ���������� 12 ��� (0x7F)
}

