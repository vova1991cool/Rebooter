#include "ISetHendler.h"

void MyDataBox::init()
{
	EEPROM.begin(DATA_SIZE + 10);
	Serial.print(F("Reading 0 bit: ")); 
	Serial.println(EEPROM.read(0));
	if(EEPROM.read(0) != 1) {
		_setDeff();
	}else
	{
		EEPROM.get(5, data);
	    serializeJson(data, Serial);
	}
	EEPROM.end();
}

void MyDataBox::_setDeff() {
	_commit("[0,\"ESP8266Default\",\"\",\"192.168.1.1\",\"192.168.1.1\"]");
}

static void(*resetFunc) (void) = 0;

void MyDataBox::_commit(const char* source) {
	Serial.println(F("Commit is started:"));
	Serial.println(source);
	EEPROM.begin(DATA_SIZE + 10);
	EEPROM.write(0, 1);
	EEPROM.put(5, source); 
	EEPROM.commit();
	delay(200); 
	EEPROM.end();
	resetFunc();
};

MyDataBox dataStruct;