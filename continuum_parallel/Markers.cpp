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
#include "Markers.h"
#include "Marker.h"
#include "MCamera.h"

/****************************/
/** Constructor */
Markers::Markers()
{
	//this->m_handle = Markers_New();
	this->ownedByMe = TRUE;
}

/****************************/
/** Destructor */
Markers::~Markers()
{
	//if(this->m_handle != 0 && this->ownedByMe)
		//Markers_Free(this->m_handle);
}

#if 0 // Claudio
/****************************/
/** Restore a Marker template and add it to the know Markers. If successful returns 0. Otherwise non-zero value is returned. */
int Markers::restoreTemplate( mtHandle pHandle, char* nameInP)
{
	int result;
	result = Markers_RestoreTemplate(this->m_handle, pHandle, nameInP);
	return result;
}
#endif

/****************************/
/** Store a Marker template If successful returns 0. Otherwise non-zero value is returned. */
int Markers::storeTemplate( int idx, mtHandle pHandle, char* nameInP)
{
	int result;
    mtHandle tHandle;
	result = Markers_TemplateItemGet(idx, &tHandle);
	if (result != mtOK) return result;
	result = Marker_StoreTemplate(tHandle, pHandle, nameInP);
	return result;
}


/****************************/
/** Add a template to the markers. If successful returns 0. Otherwise non-zero value is returned. */
int Markers::addTemplate(mtHandle markerHandle)
{
	int result;
	result = Markers_AddTemplate( markerHandle);
	return result;
}

/****************************/
/** Clears the templates of this marker. Returns 0 if successful. Otherwise a non_zero value is returned. */
int Markers::clearTemplates()
{
	int result;
	result = Markers_ClearTemplates();
	return result;
}


/****************************/
/** Return the handle to a collection of identified markers by the most recent processed frame. ?? */
mtHandle Markers::identifiedMarkers(MCamera *cam)
{
	mtHandle identifiedHandle = Collection_New();
	mtHandle camHandle;
	if (cam == NULL) {
		camHandle = NULL;
	} else {
		camHandle = cam->Handle();
	}
	Markers_IdentifiedMarkersGet(camHandle, identifiedHandle );
	return identifiedHandle;
}

/****************************/
/** Return the handle to a collection of unidentified vectors by the most recent processed frame. */
mtHandle Markers::unidentifiedVectors(MCamera *cam)
{
	mtHandle unidentifiedHandle = Collection_New();
	mtHandle camHandle;
	if (cam == NULL) {
		camHandle = NULL;
	} else {
		camHandle = cam->Handle();
	}
	Markers_UnidentifiedVectorsGet(camHandle, unidentifiedHandle);
	return unidentifiedHandle;
}

/****************************/
/** Return the value for the predictive frames interleave */
int Markers::getPredictiveFramesInterleave()
{
	int level ;
	Markers_PredictiveFramesInterleaveGet( &level);
	return level;
}

/****************************/
/** Set the value of the predictive frames interleave. */
void Markers::setPredictiveFramesInterleave(int level)
{
	Markers_PredictiveFramesInterleaveSet( level);
}

/****************************/
/** Return the value for the extrapolated frames */
int Markers::getExtrapolatedFrames()
{
	int result;
	Markers_ExtrapolatedFramesGet(&result);
	return result;
}

/****************************/
/** Set the value of the extrapolated frames */
void Markers::setExtrapolatedFrames(int newval)
{
	Markers_ExtrapolatedFramesSet(newval);
}

/****************************/
/** Return the value for the smaller XP footprint flag */
bool Markers::getSmallerXPFootprint()
{
	bool result;
	result = Markers_SmallerXPFootprint();
	return result;
}

/****************************/
/** Set the value of the smaller XP footprint flag */
void Markers::setAutoAdjustShortCycleHdrExposureLockedMarkers(bool newval)
{
	Markers_AutoAdjustShortCycleHdrExposureLockedMarkersSet(newval);
}

/****************************/
/** Return the value for the smaller XP footprint flag */
bool Markers::getAutoAdjustShortCycleHdrExposureLockedMarkers()
{
	bool isEnabled;
	Markers_AutoAdjustShortCycleHdrExposureLockedMarkersGet(&isEnabled);
	return isEnabled;
}

void Markers::setAutoAdjustHdrExposureLockMarkersNames(char* name1, char* name2)
{
	Markers_AutoAdjustHdrExposureLockMarkersNamesSet(name1, name2);
}

void Markers::getAutoAdjustHdrExposureLockMarkersNames(std::string &name1, std::string &name2)
{

	char tempString1[400];
	char tempString2[400];

	memset((void *)tempString1, 0, sizeof(tempString1));
	memset((void *)tempString2, 0, sizeof(tempString2));

	//char ptr1[MT_MAX_STRING_LENGTH];
	//char ptr2[MT_MAX_STRING_LENGTH];
	//int length;
	Markers_AutoAdjustHdrExposureLockMarkersNamesGet(tempString1, tempString2);

	name1 = std::string(tempString1);
	name2 = std::string(tempString2);

}

/****************************/
/** Set the value of the smaller XP footprint flag */
void Markers::setSmallerXPFootprint(bool newval)
{
	Markers_SmallerXPFootprintSet(newval);
}

/****************************/
/** Return the value of the templateMatchToleranceMM */
double Markers::getTemplateMatchToleranceMM()
{
	double toleranceVal = 0;
	Markers_TemplateMatchToleranceMMGet( &toleranceVal);
	return toleranceVal;
}

/****************************/
/** Set the value of the templateMatchToleranceMM */
void Markers::setTemplateMatchToleranceMM(double newVal)
{
	Markers_TemplateMatchToleranceMMSet( newVal);
}

/****************************/
/** Returns the number of templates. */
int Markers::getTemplateCount()
{
	return Markers_TemplatesCount();
}


/****************************/

void Markers::setAutoAdjustCam2CamRegistration( bool newVal)
{
	Markers_AutoAdjustCam2CamRegistrationSet( newVal);
}

/****************************/
/**  */
bool Markers::getAutoAdjustCam2CamRegistration()
{
	bool val ;
	Markers_AutoAdjustCam2CamRegistrationGet( &val);
	return val;
}


/****************************/
/** Returns the handle to the template item with the index number of idx . */
mtHandle Markers::getTemplateItem(int idx)
{
	mtHandle result = 0;
	Markers_TemplateItemGet( idx, &result);
	return result;
}

/****************************/
/** Returns the name of the template item with the index number of idx. */
mtCompletionCode Markers::getTemplateItemName(int idx, std::string &templateName)
{
	mtHandle markerHandle = this->getTemplateItem(idx);
	
	memset((void *)tempString, 0 , sizeof(tempString));
	int b;
	mtCompletionCode status = Marker_NameGet( markerHandle, tempString, sizeof(tempString), &b);
	if ( status == mtOK) {
		tempString[b] = '\0';
	}
	templateName = std::string(tempString);

	return status;
}

/****************************/
/** Returns the name of the template item with the handle of handle. */
mtCompletionCode Markers::getTemplateItemHName(mtHandle handle, std::string &templateName)
{
	memset((void *)tempString, 0 , sizeof(tempString));
	int b;
	mtCompletionCode status = Marker_NameGet( handle, tempString, sizeof(tempString), &b);
	if ( status == mtOK) {
		tempString[b] = '\0';
	}
	templateName = std::string(tempString);
	return status;
}

/****************************/
/** */
int Markers::setTemplateItemName(int idx, char* name)
{
	mtHandle markerHandle = this->getTemplateItem(idx);
	return Marker_NameSet(markerHandle, name); 
}

/****************************/
/** Processes the current frame of the default camera. */
int Markers::processFrame(MCamera *cam)
{
	mtHandle camHandle;
	if (cam == NULL) {
		camHandle = NULL;
	} else {
		camHandle = cam->Handle();
	}

	return Markers_ProcessFrame( camHandle);
}

/****************************/
bool Markers::getBackGroundProcess()
{
	bool result;
	Markers_BackGroundProcessGet(&result);
	return result;
}

/****************************/
/** Set the value of the smaller XP footprint flag */
void Markers::setBackGroundProcess(bool newval)
{
	Markers_BackGroundProcessSet(newval);
}

mtHandle Markers::getIdentifiedMarkersFromBackgroundThread(MCamera *cam)
{
	mtHandle camHandle;
	if (cam == NULL) {
		camHandle = NULL;
	} else {
		camHandle = cam->Handle();
	}

	return Markers_GetIdentifiedMarkersFromBackgroundThread(camHandle);
}