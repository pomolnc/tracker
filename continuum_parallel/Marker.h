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
#ifndef __MARKER_H__
#define __MARKER_H__

#include "MTC.h"
//#include <cstdlib>
#include "Collection.h"
#include "MCamera.h"
#include "Facet.h"
#include "Xform3D.h"
#include "Persistence.h"
using namespace MTCollection;


namespace MTMarker
{
class Marker
{
public:
	Marker(mtHandle h=0);
	~Marker();
	inline mtHandle getHandle(){ return m_handle; };

	mtHandle getTemplateFacets();
	int restoreTemplate(int persistenceHandle, const char* name);
	
	char* getName();
	void setName(char* name);
	bool wasIdentified(MCamera *cam);
	Xform3D* marker2CameraXf(mtHandle camHandle);
	Xform3D* tooltip2MarkerXf();
	mtHandle identifiedFacets (MCamera *cam);
	// void setJitterFilteringFraction(double newVal); // Claudio
	 // double getJitterFilteringFraction();
	int addTemplateFacet(Facet* newFacet, Xform3D* facet1ToNewFacetXf);
	bool validateTemplate(double positionToleranceMM, string complString);
	int storeTemplate(Persistence* p, const char* name);

private:
	mtHandle m_handle;
	bool ownedByMe;
	char m_MarkerName[400];

};
};

#endif
