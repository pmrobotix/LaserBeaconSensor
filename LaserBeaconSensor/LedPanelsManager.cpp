
#include "LedPanelsManager.h"

#include <Arduino.h>
#include <BeaconDetectionModel.h>
#include <Printable.h>
#include <USBAPI.h>
#include <WString.h>

#include <SoftI2CMaster.h>


LedPanelsManager::LedPanelsManager(unsigned long timeBetweenSendToLedPanelsMs) {
	this->timeBetweenSendToLedPanelsMs = timeBetweenSendToLedPanelsMs;
	this->lastSentToLedPanelsMs = 0;

	if(!i2c_init()) {
		Serial.println(F("WARN: I2C Soft bus is locked."));
	}
}

void LedPanelsManager::sendDetectedBeaconsIfRequired(BeaconDetectionModel bdm) {
	if( ! isTimeToSend() ) return;

	bdm.serialize();

	uint8_t salveAddr = 0; // broadcast

	i2c_start(salveAddr*2 | I2C_WRITE); //convert addr to 8bit
	write(bdm.serializedBuffer, sizeof(bdm.serializedBuffer));
	i2c_stop();

#ifdef I2CDEBUG
		Serial.println(F("Sent to I2C soft."));
#endif
}

//private methods

void LedPanelsManager::write(const uint8_t *data, size_t quantity) {
	for(size_t i = 0; i < quantity; ++i){
    	i2c_write(data[i]);
    }
}

bool LedPanelsManager::isTimeToSend() {
	unsigned long now = millis();
	if(now > lastSentToLedPanelsMs + timeBetweenSendToLedPanelsMs) {
		lastSentToLedPanelsMs = now;
		return true;
	} else {
		return false;
	}
}
