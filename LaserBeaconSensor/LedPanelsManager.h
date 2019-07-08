#ifndef _LedPanelsManager_H_
#define _LedPanelsManager_H_

#include "BeaconDetectionModel.h"
#include <Arduino.h>


// *** I2C Soft, see http://playground.arduino.cc/Main/SoftwareI2CLibrary
// put this in .ccp and not in .h
/*
#define SCL_PIN 5 // pin 5 of port B = digital pin 11 of Arduino Mega 2560
#define SCL_PORT PORTB
#define SDA_PIN 7 // pin 7 of port B = digital pin 13 of Arduino Mega 2560
#define SDA_PORT PORTB
*/

// Arduino Pro Micro avec ATMega32U4
// see https://www.arduino.cc/en/Hacking/PinMapping32u4
//#define SCL_PIN 4 // pin 4 of port B = digital pin 8 of ATMega32U4
//#define SCL_PORT PORTB
//#define SDA_PIN 5 // pin 5 of port B = digital pin 9 of ATMega32U4
//#define SDA_PORT PORTB
#define SCL_PIN 3 // pin 3 of port B =  MISO of ATMega32U4
#define SCL_PORT PORTB
#define SDA_PIN 2 // pin 2 of port B =  MOSI of ATMega32U4
#define SDA_PORT PORTB

#define I2C_TIMEOUT	100 // ms


class LedPanelsManager {
public:
	LedPanelsManager(unsigned long timeBetweenSendToLedPanelsMs);
	void sendDetectedBeaconsIfRequired(BeaconDetectionModel beaconDetectionModel);

private:
	void write(const uint8_t *data, size_t quantity);
	bool isTimeToSend();

	unsigned long timeBetweenSendToLedPanelsMs;
	unsigned long lastSentToLedPanelsMs;
};


#endif //_LedPanelsManager_H_
