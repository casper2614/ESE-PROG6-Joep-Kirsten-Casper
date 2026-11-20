#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "config.hpp"
#include "thermometer.h"

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void connectWiFi()
{
	if (WiFi.status() == WL_CONNECTED)
		return;

	WiFi.mode(WIFI_STA);
	WiFi.begin(Config::WIFI_SSID, Config::WIFI_PASSWORD);
	Serial.print("Connecting to Wi-Fi");

	while (WiFi.status() != WL_CONNECTED)
	{
		Serial.print(".");
		delay(500);
	}

	Serial.println("\nWiFi connected, IP: " + WiFi.localIP());
}

void onMqttMessage(char *topic, uint8_t *payload, unsigned int length)
{
	String msg;
	msg.reserve(length);

	for (unsigned int i = 0; i < length; i++)
		msg += (char)payload[i];

	msg.trim();

	Serial.print("RX [");
	Serial.print(topic);
	Serial.print("]: ");
	Serial.println(msg);

	// Do something with the message..
}

void connectMqtt()
{
	if (mqttClient.connected())
		return;

	mqttClient.setServer(Config::MQTT_IP, Config::MQTT_PORT);
	mqttClient.setCallback(onMqttMessage);

	// Should check for SUBACK response from broker
	while (!mqttClient.connected())
	{
		Serial.print("Connecting to MQTT broker");
		Serial.print(".");

		if (mqttClient.connect(Config::MQTT_CLIENT_ID))
		{
			Serial.println("connected!");
			mqttClient.subscribe(Config::MQTT_TOPIC_CMD);
			Serial.print("Subscribed to ");
			Serial.println(Config::MQTT_TOPIC_CMD);
		}
		else
		{
			Serial.print("failed (rc=");
			Serial.print(mqttClient.state());
			Serial.println("), retrying in 2s");

			delay(2000);
		}
	}
}

void setup()
{
	Serial.begin(115200);
	delay(1000);
}

void loop()
{
	connectWiFi();
	connectMqtt();

	mqttClient.loop(); // Checks for incoming messages

	String payload = "some_event/some_value";
	if (mqttClient.publish(Config::MQTT_TOPIC_STATE, payload.c_str())) {
		Serial.print("TX [");
		Serial.print(Config::MQTT_TOPIC_STATE);
		Serial.print("]: ");
		Serial.println(payload);
	}
}