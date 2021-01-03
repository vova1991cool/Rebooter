// 
// 
// 

#include "IServerProcess.h"

void IServerProcessClass::init(JsonArray &_data)
{
	int indexMode = _data[MODE];
	WiFi.mode(indexMode ? WIFI_STA:WIFI_AP);

	
	IPAddress _ip;
	_ip.fromString(_data[HOST].as<char*>());
	IPAddress _gateway;
	_gateway.fromString(_data[GATEWAY].as<char*>());

	if (indexMode) {
		WiFi.config(_ip, _gateway, IPAddress(255,255,255,0));
		WiFi.begin(_data[SSID].as<char*>(), _data[PASS].as<char*>());
		Serial.print(F("Try to connect."));
		while (WiFi.status() != WL_CONNECTED)
		{
			Serial.print(".");
			delay(500);
		}
		Serial.print("Connected! IP: ");
		Serial.println(WiFi.localIP());
	}
	else {
		WiFi.softAPConfig(_ip, _gateway, IPAddress(255,255,255,0));
	    WiFi.softAP(_data[SSID].as<char*>(), _data[PASS].as<char*>());
	}

	Serial.println(MDNS.begin("myrebooter.com", _ip) ? F("mDNS responder started") : F("Error setting up MDNS responder!"));

	begin(80);
	
	on("/", HTTP_GET, []() {
		//Serial.println(HTML_PAGE);
		IServerProcess.send(200, "text/html", HTML_PAGE);
	});

	on(F("/getData"), HTTP_GET, []() {
		Serial.print(F("Sending data to client: "));
		serializeJson(dataStruct._getData(), Serial);
		char dataToSend[DATA_SIZE];
		serializeJson(dataStruct._getData(), dataToSend);
		IServerProcess.send(200, "application/json", dataToSend);
	});

	on("/saveData", HTTP_POST, []() {
		Serial.println("Recive SaveData");
		Serial.println(IServerProcess.arg(0));
		IServerProcess.send(200, "application/text", "ok");
		char buffer[DATA_SIZE];
	    IServerProcess.arg(0).toCharArray(buffer, DATA_SIZE);
		dataStruct._commit(buffer);
	});

	on("/reboot", HTTP_POST, [](){
		Serial.println("Recive RebootInit");
		Serial.println(IServerProcess.arg(0));
		digitalWrite(IServerProcess.arg(0).toInt(), LOW);
		IServerProcess.send(200, "application/text", "ok");
	});

	onNotFound([]() {
		IServerProcess.send(404, "text/plain", F("404: Not Found"));
	});

}

IServerProcessClass IServerProcess;
