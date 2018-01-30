/*
 * enumerati.h
 *
 *  Created on: 07 nov 2017
 *      Author: Luke
 */

#ifndef SMART_GARAGE_ENUMERATI_H_
#define SMART_GARAGE_ENUMERATI_H_


enum class doorstatus
{
	CLOSE,
	OPENING,
	CLOSING,
	OPEN
};

enum class detectmvstatus
{
	IDLE,
	DM0,
	DM1
};

enum class proxstatus
{
	IDLE,
	TOODIST,
	APPROACH,
	INSIDE,
	CANSTOP,
	TOUCH
};

#endif




