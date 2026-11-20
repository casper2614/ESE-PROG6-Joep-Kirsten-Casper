#pragma once

// What should the thermometer do?
class Thermometer {
	public:
		Thermometer();

		[[nodiscard("Reading temperature without using the value is likely a bug")]] float readTempC() const;

		~Thermometer();
};