// Do not remove the include below

#include "LaserBeaconSensorLedPanel.h"

#include <Rainbowduino.h>



void setup() {
	//Rb.init(); //-> in BeaconVisualusation

	sprintf(&cPANELNUMBER, "%d", PANEL_NUMBER); //conversion byte to char

	Wire.begin(MY_I2C_ADDRESS);                // join i2c bus with address...

	TWAR = (MY_I2C_ADDRESS << 1) | 1;  // enable broadcasts to be received

	Wire.onReceive(receiveEvent); // register event
	Serial.begin(115200);           // start serial for output

	Serial.print(F("BeaconDetectorLedPannel Console! - "));
	Serial.print(F("PANEL_NUMBER="));
	Serial.print(PANEL_NUMBER);
	Serial.print(F(" MY_I2C_ADDRESS="));
	Serial.print(MY_I2C_ADDRESS);
	Serial.println();


	beaconVisualusation.startDisplay();

}

void loop() {
	// log last beacon received (console unavailable in interruption)
	if(DEBUG) beaconDetectionModel.logToConsole();

	if(showEye) {
		beaconVisualusation.showNumber();

	}

	delay(500);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
//int howmany
void receiveEvent(int ) {
	// !! serial not available (in interrupt) !!
	//Serial.println(F("receiveEvent..."));

	int i = 0;
	while (Wire.available()) {
		beaconDetectionModel.serializedBuffer[i] =  Wire.read();
		i++;
	}

	beaconDetectionModel.deserialize();
	onBeaconDetectionModelReceived();
}

void onBeaconDetectionModelReceived() {
	//if(DEBUG) Serial.println(F("onBeaconDetectionModelReceived..."));
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool forThisPanel = false;
	bool firstBeaconForThisPanel = true;

	for(int i=0; i<beaconDetectionModel.detectedBeaconCount; i++) {
		if(beaconVisualusation.drawBeacon(
				beaconDetectionModel.angleInDeg[i],
				beaconDetectionModel.distToBeaconCenterInCm[i],
				beaconDetectionModel.flags[i],
				firstBeaconForThisPanel)) {

			forThisPanel = true;
			firstBeaconForThisPanel = false;
		}
	}

	showEye = ! forThisPanel;
}
