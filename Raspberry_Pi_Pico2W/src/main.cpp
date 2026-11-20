#include <Arduino.h>
#include <WiFi.h>

const char* WIFI_SSID = "";
const char* WIFI_PASS = "";

constexpr uint16_t MQTT_PORT = 1883;

WiFiServer mqttServer(MQTT_PORT);

void setup() {
	Serial.begin(115200);

	delay(1500);

	WiFi.begin(WIFI_SSID, WIFI_PASS);
	while(WiFi.status() != WL_CONNECTED) {
		Serial.println('.');
		delay(500);
	}

	Serial.println("\nConnected to Wi-Fi");
	Serial.print("Pico 2 W IP: ");
	Serial.println(WiFi.localIP());

	mqttServer.begin();
	Serial.println("Listening for TCP/MQTT connections on port " + MQTT_PORT);
}

void loop() {
}