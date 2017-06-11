/**************************************************************
*
*     Micron Tracker: Example C++ wrapper and Multi-platform demo
*   
*     Written by: 
*			Shahram Izadyar, Robarts Research Institute - London- Ontario , www.robarts.ca
*			Claudio Gatti, Claron Technology - Toronto -Ontario, www.clarontech.com
*
*     Copyright Claron Technology 2000-2013
*
***************************************************************/
#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "MTC.h"

class Vector
{
public:
	Vector(mtHandle h =0);
	~Vector();
	mtHandle Handle();

	int getEndPos2x3(double* result);
	int setEndPos2x3(double* newPos2x3);
	int getEndXPoints(double* result);



private:
	mtHandle m_handle;
	bool ownedByMe;
};

#endif