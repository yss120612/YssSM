// 
// 
// 

#include "Log.h"


String Logg::getAll(String divider) {
	String result = "";
	for (uint16_t i = 0; i < _log.size(); i++) {
		result += _log[i];
		if (i != _log.size() - 1) {
			result += divider;
		}
	}
	return result;
}

void Logg::logging(String s)
 {
#ifdef _SERIAL
	Serial.println(s);
#endif // _SERIAL

	if (_log.length() >= maxCount) {
		_log.pop_front();
	}
	else
	_log.push_back(s);
	}