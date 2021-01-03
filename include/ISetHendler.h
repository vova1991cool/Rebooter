// ISetHendler.h

#ifndef _ISETHENDLER_h
#define _ISETHENDLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <EEPROM.h>
#include <Stream.h>
#include "ArduinoJson.h"

/*[0,"dsfgdgs","234235","192.168.1.1","255.255.255.0",1,1,"0965622167",0,"#31#"]*/

#define DATA_SIZE 256

/*SETTINGS ENUM*/
enum dataIndexEnum{
	MODE,
	SSID,
	PASS,
	HOST,
	GATEWAY
};

struct MyDataBox
	{
		StaticJsonDocument<DATA_SIZE>& _getData() { return data; };

		StaticJsonDocument<DATA_SIZE> data; //global settings buffer

		void init(); //settings initialization

		void _setDeff(); //seting defoult

		void _commit(const char* source); //method for commiting

	};

	const size_t _dataSize = sizeof(MyDataBox) + 10;

    extern MyDataBox dataStruct;
#endif