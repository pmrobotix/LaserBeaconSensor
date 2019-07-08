// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _LaserBeaconSensorLedPanel_H_
#define _LaserBeaconSensorLedPanel_H_

#include <Arduino.h>
#include <BeaconDetectionModel.h>

#include "BeaconVisualusation.h"
#include <HardwareSerial.h>
#include <Wire.h>
#include <WString.h>

//configuration parameters
const byte PANEL_NUMBER = 1;
const bool DEBUG = false;



bool showEye = true;
char cPANELNUMBER = ' ';
const byte MY_I2C_ADDRESS = PANEL_NUMBER;

BeaconDetectionModel beaconDetectionModel;
BeaconVisualusation beaconVisualusation(PANEL_NUMBER); // panel number

//add your function definitions for the project LaserBeaconSensorLedPanel here

void onBeaconDetectionModelReceived();
void receiveEvent(int howMany);

//Do not add code below this line
#endif /* _LaserBeaconSensorLedPanel_H_ */
