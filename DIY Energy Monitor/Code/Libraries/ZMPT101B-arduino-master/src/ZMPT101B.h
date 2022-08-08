#ifndef ZMPT101B_h
#define ZMPT101B_h

#include <Arduino.h>

#define ADC_SCALE 4095.0
#define VREF 3.3
#define DEFAULT_FREQUENCY 50

class ZMPT101B {
public:
	ZMPT101B(uint8_t _pin);
	int calibrate();
	void setZeroPoint(int _zero);
	void setSensitivity(float sens);
	float getVoltageDC();
	float getVoltageAC(uint16_t frequency = 50);
	int getZeroPoint();

private:
	int zero = 512;
	float sensitivity;
	uint8_t pin;
};

#endif