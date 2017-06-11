/**************************************************************
*
*     Micron Tracker: Example C++ wrapper and Multi-platform demo
*   
*     Written by: 
*			Shahram Izadyar, Robarts Research Institute - London- Ontario , www.robarts.ca
*			Claudio Gatti, Ahmad Kolahi, Claron Technology - Toronto -Ontario, www.clarontech.com
*
*     Copyright Claron Technology 2000-2013
*
***************************************************************/
#ifndef __FACET_H__
#define __FACET_H__

#include "MTC.h"
#include <cstdlib>
#include "MCamera.h"
#include "Vector.h"
#include "Collection.h"
#include "Xform3D.h"
#include <iostream>
using namespace MTCollection;


class Facet
{
public:
	Facet(mtHandle h =0);
	~Facet();
	inline mtHandle getHandle(){ return m_handle; };
	int getXpoints( MCamera *cam, double *result2x3x2x2); //[LV/SV][L/R/M][base/head][X/Y]
	vector<Vector *> IdentifiedVectors();
	vector<Vector *> TemplateVectors();
	bool setVectorsFromSample(vector<MTCollection::Collection*> &sampledVectorSets, string &outCompletionExplanation , double maxSampleErrorAllowedMM = 2.0);
	bool validateTemplate(double positionToleranceMM, string outCompletionString = NULL);
	bool identify(MCamera* cam, vector<Vector*> vectorSet, double positionToleranceMM);
	Xform3D* getFacet2CameraXf(MCamera* cam);


private:
	mtHandle m_handle;
	bool ownedByMe;
};

#endif
