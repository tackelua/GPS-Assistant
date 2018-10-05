// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       Gith Assistant.ino
    Created:	15-Aug-18 07:17:36
    Author:     GITH\tacke
*/

// Define User Types below here or use a .h file
//


// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//

// The setup() function runs once each time the micro-controller starts
#include <WiFiUdp.h>
#include <WiFiServerSecure.h>
#include <WiFiServer.h>
#include <WiFiClientSecure.h>
#include <WiFiClient.h>
#include <ESP8266WiFiType.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServerSecure.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <BlynkSimpleEsp8266.h>
#include <TimeLib.h>
#include <Time.h>
#include <WidgetRTC.h>

#define VERSION		"0.1"
#define BLYNK_AUTH	"7d7bc8e99cff4a32abcf737c6bbdd40c"
#define BLYNK_HOST	"gith.cf"
#define BLYNK_PORT	8442
#define BLYNK_RELAY	V2
#define BLYNK_IN	V0
#define BLYNK_OUT	V1
#define RELAY		D1

WidgetRTC rtc;

void setup()
{
	pinMode(RELAY, OUTPUT);
	Serial.begin(74880);
	Serial.setTimeout(10);
	Serial.println("Version: " VERSION);

	WiFi_init();
	Blynk_init();
	Serial.println(F("\nDone."));
}

// Add the main program code into the continuous loop() function
void loop()
{
	Blynk.run();
}

void WiFi_init() {
	WiFi.setAutoConnect(true);
	WiFi.setAutoReconnect(true);
	WiFi.mode(WIFI_STA);
	Serial.println(F("\nWiFi_init"));
	
	WiFiManager wifiManager;
	wifiManager.autoConnect("GPS Assistant");

	Serial.print(F("IP: "));
	Serial.println(WiFi.localIP());
}

void Blynk_init() {
	Serial.println(F("\nBlynk_init"));
	Blynk.config(BLYNK_AUTH, BLYNK_HOST, BLYNK_PORT);
	while (Blynk.connect() != true) {
		Serial.print(F("."));
		delay(100);
	}
}

BLYNK_CONNECTED() {
	rtc.begin();
	Blynk.notify("Hardware connected");
}

//Get In the region
BLYNK_WRITE(BLYNK_IN) {
	int val = param.asInt();
	if (val = true) {
		Serial.println("GET IN");
		digitalWrite(RELAY, HIGH);
		Blynk.virtualWrite(BLYNK_RELAY, HIGH);
		Blynk.notify("Enter an area.");
	}
}
//Get Out the region
BLYNK_WRITE(BLYNK_OUT) {
	int val = param.asInt();
	if (val = true) {
		Serial.println("GET OUT");
		digitalWrite(RELAY, LOW);
		Blynk.virtualWrite(BLYNK_RELAY, LOW);
		Blynk.notify("Exit an area.");
	}
}
//Control the button
BLYNK_WRITE(BLYNK_RELAY) {
	int val = param.asInt();
	digitalWrite(RELAY, val);
	String n = "Control ";
	n += val ? "ON" : "OFF";
	Serial.println(n);
	Blynk.notify(n);
}