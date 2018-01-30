#ifndef __SHARED__
#define __SHARED__

#include "enumerati.h"

class Shared {
public:
	Shared();
	scanstatus getRStatus();
	void setRStatus(scanstatus rStatus);

private:
	scanstatus received_status;
};

#endif
