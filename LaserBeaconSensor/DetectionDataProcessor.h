
#ifndef _DetectionDataProcessor_H_
#define _DetectionDataProcessor_H_

#include "RawDetectionData.h"
#include "BeaconDetectionModel.h"

//décalage d'angle en degrés, dépend de la conception de la balise
#define ALPHA_REF_DEGREES_FLOAT -25.0f //-79
//distance maximum de détection en cm
#define MAX_DIST_CM_FLOAT 255.0f


class DetectionDataProcessor {

public:
	void processRawData(RawDetectionData &inTimings, BeaconDetectionModel &outModel);

private:
	/** Dist = from the center of the detector to the center of the beacon  (in meters) */
	float getDistInM(unsigned long t1, unsigned long t2, unsigned long tB_tA);

	float getAngleInDeg(unsigned long t1, unsigned long t2, unsigned long tB_tA);

	bool isInBlindSpot(unsigned long t1, unsigned long t2, unsigned long tB_tA);
	bool isInBlindSpot(float a);


	unsigned long tD[MAX_NBR_OF_BEACONS];

	/** time in microseconds of laser signal rise (end of beacon detection) */
	unsigned long tU[MAX_NBR_OF_BEACONS];

	int detectedBeaconCount;
};


#endif //_DetectionDataProcessor_H_
