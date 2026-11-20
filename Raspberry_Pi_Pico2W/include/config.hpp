#pragma once

#include <stdint.h>

namespace Config {
	constexpr const char* WIFI_SSID     = "PI_HOTSPOT_SSID";
	constexpr const char* WIFI_PASSWORD = "PI_HOTSPOT_PASSWORD";
	constexpr const char* MQTT_IP		= "PI_MQTT_BROKER_IP";
	constexpr uint16_t MQTT_PORT 		= 1883;
	constexpr const char* MQTT_CLIENT_ID     		= "pico2w_therm_1";
	constexpr const char* MQTT_TOPIC_STATE   		= "sim/device/pico_therm_1/state";
	constexpr const char* MQTT_TOPIC_CMD     		= "sim/device/pico_therm_1/cmd";
}
