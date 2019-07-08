#include "BeaconVisualusation.h"

#include <Arduino.h>
#include <BeaconDetectionModel.h>
#include <HardwareSerial.h>
#include <Rainbowduino.h>
#include <stdio.h>


const uint32_t GREEN = 0x00FF00;
const uint32_t ORANGE = 0xFF8C00;
const uint32_t RED = 0xFF0000;
const uint32_t BLUE = 0x0000FF;
/*
Public fieldStatic member	Black
Represents a black color (RGB = 0x000000).
Public fieldStatic member	Blue
Represents a blue color (RGB = 0x0000FF).
Public fieldStatic member	Brown
Represents a brown color (RGB = 0xA52A2A).
Public fieldStatic member	Cyan
Represents a cyan color (RGB = 0x00FFFF).
Public fieldStatic member	DarkBlue
Represents a dark blue color (RGB = 0x000080).
Public fieldStatic member	DarkCyan
Represents a dark cyan color (RGB = 0x008080).
Public fieldStatic member	DarkGray
Represents a dark gray color (RGB = 0x808080).
Public fieldStatic member	DarkGreen
Represents a dark green color (RGB = 0x008000).
Public fieldStatic member	DarkMagenta
Represents a dark magenta color (RGB = 0x800080).
Public fieldStatic member	DarkRed
Represents a dark red color (RGB = 0x800000).
Public fieldStatic member	DarkYellow
Represents a dark yellow color (RGB = 0x808000).
Public fieldStatic member	Empty
Represents an empty color (RGB = 0x000000).
Public fieldStatic member	Gray
Represents a gray color (RGB = 0x808080).
Public fieldStatic member	Green
Represents a green color (RGB = 0x00FF00).
Public fieldStatic member	LightGray
Represents a light gray color (RGB = 0xC0C0C0).
Public fieldStatic member	Magenta
Represents a magenta color (RGB = 0xFF00FF).
Public fieldStatic member	Orange
Represents an orange color (RGB = 0xFFA500).
Public fieldStatic member	Pink
Represents a pink color (RGB = 0xFFC0CB).
Public fieldStatic member	Purple
Represents a purple color (RGB = 0x800080).
Public fieldStatic member	Red
Represents a red color (RGB = 0xFF0000).
Public fieldStatic member	White
Represents a write color (RGB = 0xFFFFFF).
Public fieldStatic member	Yellow
Represents a yellow color (RGB = 0xFFFF00).*/
BeaconVisualusation::BeaconVisualusation(int pannelNumber) {
	this->pannelNumber = pannelNumber;
	sprintf(&cPannelNumber, "%d", pannelNumber); //conversion byte to char
	Rb.init();

}

void BeaconVisualusation::startDisplay() {

	for (int i = 0; i < 5; i++) {

		Rb.blankDisplay();
		delay(100);
		Rb.drawChar(cPannelNumber, 1, 0, 0x010000); //Rouge dark
		delay(100);
	}
}

void BeaconVisualusation::showNumber() {

	Rb.blankDisplay();
	Rb.drawChar(cPannelNumber, 1, 0, 0x010000);

}

void BeaconVisualusation::clearPannel() {
	Rb.blankDisplay();
}

bool BeaconVisualusation::drawBeacon(int angle, int distInCm, uint8_t flags,
		bool firstBeaconForThisPanel) {

	// display the beacon on the opposite side of the LED panels
	//angle = angle + 180;

	// convert from -180/180 to 0/360
	int angle360 = (angle + 360) % 360;

	int column = getColumn(angle360);
	int opposite_column = getOppColumn(angle360);
	if (column == -1) {
		//return false;
	} else {
		// on led panels:
		// 0,0 is at top left; X is vertical
		// 7,7 is bottom right
		int columnOfPanel = 7 - column;

		unsigned int heigth = getHeight(distInCm); // 0->7

		uint32_t color = getColor(flags);

		if (firstBeaconForThisPanel)
			clearPannel();

		//Rb.drawLine(7 - heigth, columnOfPanel, 7, columnOfPanel, color);

		Rb.drawLine(0, columnOfPanel, heigth, columnOfPanel, color);

		return true;
	}

	if (opposite_column == -1)
		return false;
	else {
		int oppColumnOfPanel = 7 - opposite_column;
		unsigned int heigth = getHeight(distInCm); // 0->7

		uint32_t color = RED;

		if (firstBeaconForThisPanel)
			clearPannel();

		//Rb.drawLine(7 - heigth, columnOfPanel, 7, columnOfPanel, color); // de bas en haut

		Rb.drawLine(0, oppColumnOfPanel, heigth, oppColumnOfPanel, color); //de haut en bas

		return true;
	}
}
int BeaconVisualusation::getOppColumn(int angle360) {
	int panelopp;
	float angleInPanel = 0.0;
	if ((angle360 >= 45) && (angle360 < 135)) {
		panelopp = 2;
		angleInPanel = 45.0 - (angle360 - ((1) * 90.0)); //compris entre 0 et 90
	} else if ((angle360 >= 135) && (angle360 < 225)) {
		panelopp = 1;
		angleInPanel = 45.0 - (angle360 - ((2) * 90.0)); //compris entre 0 et 90
	} else if ((angle360 >= 225) && (angle360 < 315)) {
		panelopp = 4;
		angleInPanel = 45.0 - (angle360 - ((3) * 90.0)); //compris entre 0 et 90
	} else {
		panelopp = 3; // entre 315 et 45
		angleInPanel = 45.0 - (angle360 - ((4) * 90.0)); //compris entre 0 et 90
		if (angleInPanel <= 0)
			angleInPanel += 360;
		if (angleInPanel >= 360)
			angleInPanel -= 360;
	}

	if (panelopp != this->pannelNumber)
		return -1;

	//float angleInPanel = 45.0 - (angle360 - ((panelopp) * 90.0)); //compris entre 0 et 90

	float colIndex = angleInPanel / 11.25; // ready to truncate (0 to 7)
	int colIndexRounded = (int) colIndex;
	return colIndexRounded;
}
// private methods
// cho => 1=back / 2=left / 3=front / 4=right
int BeaconVisualusation::getColumn(int angle360) {
	int panel;

	if ((angle360 >= 45) && (angle360 < 135))
		panel = 4;
	else if ((angle360 >= 135) && (angle360 < 225))
		panel = 3;
	else if ((angle360 >= 225) && (angle360 < 315))
		panel = 2;
	else
		panel = 1; // entre 315 et 45
	/*
	 if (angle360 < 90)
	 panel = 4;
	 else if ((angle360 >= 90) & (angle360 < 180))
	 panel = 3;
	 else if ((angle360 >= 180) & (angle360 < 270))
	 panel = 2;
	 else
	 panel = 1;*/
	/*
	 Serial.print(" angle360 = ");
	 Serial.print(angle360);
	 Serial.print(" panel= ");
	 Serial.println(panel);
	 */
	if (panel != this->pannelNumber)
		return -1;

	//float angleInPanel = 90 - (angle360 - (4 - panel) * 90);
	float angleInPanel = 45.0 - (angle360 - ((5 - panel) * 90.0)); //compris entre 0 et 90
	if (angleInPanel <= 0)
		angleInPanel += 360;
	if (angleInPanel >= 360)
		angleInPanel -= 360;

	float colIndex = angleInPanel / 11.25; // ready to truncate (0 to 7)
	int colIndexRounded = (int) colIndex;
	/*
	 Serial.print(" angleInPanel = ");
	 Serial.print(angleInPanel);
	 Serial.print(" colIndexRounded = ");
	 Serial.print(colIndexRounded);

	 Serial.println();
	 */
	return colIndexRounded;
}

unsigned int BeaconVisualusation::getHeight(uint8_t distcm) {
	float d; // 0 to 99

	if (distcm < 30)
		distcm = 30;
	else if (distcm > 200)
		distcm = 200;

	distcm = distcm - 30;
	d = (float) distcm;

	float height = d / 25.0; // ready to truncate (0 to 7) 12.5
	int heightInt = 7 - height;
	if (heightInt < 0)
		heightInt = 0;
	/*steph
	 if (dist < 40)
	 dist = 40;
	 else if (dist > 200)
	 dist = 200;

	 dist = dist - 40;
	 d = (float) dist;

	 float height = d / 12.5; // ready to truncate (0 to 7)
	 int heightInt = height;
	 if (heightInt < 0)
	 heightInt = 0;*/
	return heightInt;
}

uint32_t BeaconVisualusation::getColor(uint8_t flags) {
	if ((flags & BeaconDetectionModel::FLAG_BLIND_SPOT)
			== BeaconDetectionModel::FLAG_BLIND_SPOT) {
		return ORANGE;
	} else {
		return GREEN;
	}
}
