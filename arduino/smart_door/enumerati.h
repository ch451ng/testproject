/*
 * enumerati.h
 *
 *  Created on: 07 nov 2017
 *      Author: Luke
 */

#ifndef SMART_GARAGE_ENUMERATI_H_
#define SMART_GARAGE_ENUMERATI_H_


enum class scanstatus
{
	IDLE,
	SCAN,
	TRACK
};


enum class loginstatus
{
	IDLE,
	REQUEST,
	FORWARDED,
	SUCCESS,
	FAIL
};

#endif




