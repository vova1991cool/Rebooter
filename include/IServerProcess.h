// IServerProcess.h

#ifndef _ISERVERPROCESS_h
#define _ISERVERPROCESS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "ESP8266WebServer.h"
#include "ESP8266mDNS.h"
#include "ESP8266HTTPClient.h"
#include "HTML_PAGE.h"

#include "ISetHendler.h"

class IServerProcessClass:public ESP8266WebServer
{
 public:
	void init(JsonArray &_data);
	void clientsHendler() { handleClient(); }
};

extern IServerProcessClass IServerProcess;

#endif