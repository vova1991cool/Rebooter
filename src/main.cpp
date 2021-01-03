#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.hpp>
#include <ArduinoJson.h>
#include "IServerProcess.h"

void setup(){
    Serial.begin(9600);
    Serial.println("Start!");

    for (size_t i = 0; i < 10; i++)
    {
        pinMode(i, OUTPUT);
    }

    dataStruct.init();

    IServerProcess.init(dataStruct._getData().as<JsonArray&>());
    
}

void loop(){
    //Server clients hendler
	IServerProcess.clientsHendler();
}