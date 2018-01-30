#ifndef __SHARED__
#define __SHARED__

#include "enumerati.h"

class Shared {
public:
	Shared();
	bool isDetected();
	void setDetected(bool detected);
	bool openRequest();
	void setOpenRequest(bool openSGN);
	bool closeRequest();
	void setCloseRequest(bool openSGN);
	bool detectorStatus();
	void setDetectorStatus(bool enableDetector);
	float getDistance();
	void setDistance(float dist);
	proxstatus getDist();
	void setDist(proxstatus dist);

private:
	bool detected;
	bool openSGN;
	bool closeSGN;
	bool enableDetector;
	float distance;
	proxstatus dist;
};

#endif
