// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _LaserBeaconSensor_H_
#define _LaserBeaconSensor_H_
#include <Arduino.h>
#include "MeanVariance.h"
#include "LedPanelsManager.h"
#include "RawDetectionData.h"
#include "DetectionDataProcessor.h"
#include "BeaconDetectionStableHolder.h"


#include <Wire.h>

const byte MY_I2C_ADDRESS = 99;

const bool DEBUG = true; //TODO here or is Eclipse Config ???
const unsigned long TIME_BETWEEN_SEND_TO_LED_PANELS_MS = 100; //ms
const unsigned long TIME_BETWEEN_SEND_TO_CONSOLE_MS = 1000; //ms

LedPanelsManager ledPanelsManager(TIME_BETWEEN_SEND_TO_LED_PANELS_MS);
DetectionDataProcessor detectionDataProcessor;
BeaconDetectionStableHolder beaconDetectionStableHolder;


unsigned long lastSentToConsoleMs=0;


const uint8_t ROTATION_SENSOR_PIN = 0;
const uint8_t LASER_PIN = 1;
const uint8_t MOTOR_PIN = 10;


/** Acquisition mode (internal) */
enum ACQ_MODE {
	ACQ_MODE_STD,
	ACQ_MODE_DISABLED,
	ACQ_MODE_LAST_ONE,

	/** end of the last_one/disabled rotation */
	ACQ_MODE_IGNORE_NEXT_LASER_UP
};

// Detection buffers
/** Current acquisition, do not read */
volatile RawDetectionData workBuffer;
volatile RawDetectionData lastStableBuffer;
volatile boolean stableBufReadInProgress = false;
volatile ACQ_MODE acqMode = ACQ_MODE_STD; // init, do not change




void interruptRotationTick();
void interruptLaser();

void readFromStableBuffer(RawDetectionData &dest);
void writeToStableBuffer();
void logRawDetectionData(RawDetectionData buf);
void onBeaconDetectionDataRequested();

bool isTimeToSendToConsole();
//Do not add code below this line
#endif /* _LaserBeaconSensor_H_ */
