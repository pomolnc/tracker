#include "processing.h"
#include "UtilityFunctions.h"
using namespace mtUtils;
//#define OPENGL
//#ifdef OPENGL
//#include "FL/gl.h"
//#endif

#if WIN32
#include <Windows.h.>
#include <direct.h>
#include <errno.h>
// FL.math creates some conflict, so declare by hand
//extern "C" {
//double  __cdecl cos(double);
//double  __cdecl sin(double);
//}
#else
#include <math.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

bool left_turn;

Processing::Processing()
{
    this->pPers = new Persistence();
    this->pMarkers = new Markers();
    this->isShowingVectors = true;
    this->isShowingHalfSize = false;
    this->isShowingXpoints = false;
    this->isDisplayEnabled = true;
    this->isMarkersProcessingEnabled = true;
    this->isXPointsProcessingEnabled = true;
    this->isHdrModeEnabled = false;
    this->isHdrLockedMarkerEnabled = false;
    this->isBackGroundProcessingEnabled = false;
    this->isCam2CamRegistered = true;
    this->isSingleWindow = false;
    this->isCollectingSamples = false;
    this->isAdditionalFacetAdding = false;
    this->m_collectedSampleFrames = 0;
    this->isShowingPositions = true;
    this->isCaptureEnabled = true;
    this->isShowingAngleAndDistance = true;
    this->isMarkerTemplatesInitialized = false;
    this->isOptionsInitialized = false;
//    this->markersListBuffer = NULL;
//    this->markersList = NULL;


    this->pCurrCam = NULL;
//	Fl::gl_visual(FL_RGB);

#ifdef WIN32
    // initialize LUT for Display
    for (int i=0; i < 256;i++) {
        this->LUT[i].rgbBlue = i;
        this->LUT[i].rgbGreen = i;
        this->LUT[i].rgbRed = i;

    }
#endif

}

/****************************/
/** Destructor */
Processing::~Processing()
{

}

/****************************/
/** */
void Processing::initialINIAccess()
{
    char currDir[255];
    mtUtils::getCurrPath(currDir);
    #ifdef WIN32
        strcat(currDir,"\\MTDemoCPP.ini");
    #else
        strcat(currDir,"/MTDemoCPP.ini");
    #endif
        this->pPers->setPath(currDir);

        this->pPers->setSection ("General");
    #if 0
        //Setting the FrameInterleave property in the Markers object
        int defaultFrameInterleave = 0;
        this->pMarkers->setPredictiveFramesInterleave( this->pPers->retrieveInt("PredictiveFramesInterleave", defaultFrameInterleave) );
    #endif

        //Setting the TemplateMatchToleranceMM property in the Markers object
        double defaultTempMatchToleranceMM = 1.0;
        double defaultLightCoolness = 0.1;

        this->pMarkers->setTemplateMatchToleranceMM( this->pPers->retrieveDouble("TemplateMatchToleranceMM", defaultTempMatchToleranceMM) );
        this->lightCoolness = this->pPers->retrieveDouble("LightCoolness", defaultLightCoolness);

        int s = (this->pPers->retrieveInt("SingleWindow", 1) );
        isSingleWindow = (s == 0? true:true);
        s = (this->pPers->retrieveInt("UseOpenGL", 1) );
        useOpenGL = (s == 0? false:true);
        cout << "Open Gl: " << useOpenGL<< endl;

        bool defaultSmallerXPFootprint = true;
        int defaultExtrapolatedFrames = 5;

        bool SmallerXPFootprint = (bool)(this->pPers->retrieveInt("DetectSmallMarkers", defaultSmallerXPFootprint));
        int ExtrapolatedFrames = this->pPers->retrieveInt("ExtrapolatedFrames", defaultExtrapolatedFrames);

        this->pMarkers->setSmallerXPFootprint(SmallerXPFootprint);
        this->pMarkers->setExtrapolatedFrames(ExtrapolatedFrames);

        //could have been clipped
        this->pPers->saveInt("ExtrapolatedFrames", this->pMarkers->getExtrapolatedFrames());

        //Test if Markers dir exists, otherwise create
        char currPath[255];
        mtUtils::getCurrPath(currPath);
    #ifdef WIN32
        strcat(currPath, "\\Markers\\");
    #else
        strcat(currPath, "/Markers/");
    #endif


//    #ifdef WIN32
//        int result = _mkdir(currPath);
//        if (result != 0 && errno != EEXIST) {
//            fl_message("Could not create Markers folder! Please create it manually.");
//            return;
//        }

//    #else
//        int result = mkdir(currPath, 777);
//        int e = errno;
//        if (result != 0 && e != EEXIST) {
//            fl_message("Could not create Markers folder! Please create it manually.");
//            return;
//        }
//    #endif

}

/****************************/
/** */
void Processing::setupCameras()
{
    this->pCameras = new Cameras();
    int result = this->pCameras->AttachAvailableCameras();

    if (result == 0 &&  this->pCameras->getCount() >= 1 ) {
        //this->pCurrCam = this->pCameras->m_vCameras[0];
        this->pCurrCam = this->pCameras->getCamera(0); //construct a MCamera with a camera handle
        cout<<this->pCurrCam<<endl;
        if (this->pCurrCam->getXRes() > 1200 ) this->isShowingHalfSize = true;
        cout << " Camera attached successfully " << endl;
    } else {
        cout << " No camera available or missing calibration file. Please also check that MTHome system environment variable is set " << endl;
//        fl_message(" No camera available or missing calibration file. Please also check that MTHome system environment variable is set ");
        exit(1);
    }
}

/****************************/
/** */
void Processing::detach()
{
    this->pCameras->Detach();
}

/****************************/
/** */
void Processing::refreshMarkerTemplates()
{
//	vector<string> templateNames;
//	mtUtils::getFileNamesFromDirectory( templateNames,"Markers", true);

//	int result = 0;
//	result = this->pMarkers->clearTemplates();
//		cout << "Cleared templates..." << endl;


//	char currentFolderPath[MT_MAX_STRING_LENGTH];
//	mtCompletionCode st;

//	mtUtils::getCurrPath(currentFolderPath);
//#ifdef WIN32
//		strcat(currentFolderPath, "\\Markers\\");
//#else
//		strcat(currentFolderPath, "/Markers/");
//#endif

//	st = Markers_LoadTemplates(currentFolderPath);
}

void Processing::EnableHdrLockedMarkers(bool newVal)
{
    // direct call to the MTC API
    //Markers_AutoAdjustShortCycleHdrExposureLockedMarkersSet(true);
    //Markers_AutoAdjustHdrExposureLockMarkersNamesSet("DrillTag", "JawTag");

    // Use the Wrapper
//    this->pMarkers->setAutoAdjustShortCycleHdrExposureLockedMarkers(newVal);
//    this->pMarkers->setAutoAdjustHdrExposureLockMarkersNames("DrillTag", "JawTag");

    // retrieving values
    //bool isHdrLockedMarkerEnabled = this->pMarkers->getAutoAdjustShortCycleHdrExposureLockedMarkers();
    //std::string MarName1;
    //std::string MarName2;
    //this->pMarkers->getAutoAdjustHdrExposureLockMarkersNames(MarName1, MarName2);
}

/****************************/
/** */
int Processing::processCurrFrame(bool withDisplay)
{
    if (this->pMarkers->getBackGroundProcess() == false) {
        if (isMarkersProcessingEnabled)
            this->pMarkers->processFrame(NULL);
        if (isXPointsProcessingEnabled)
            this->pXPoints->processFrame(NULL);
    }

    this->pPers->setSection ("General");
    int s = (this->pPers->retrieveInt("AutoCool", 1) );
    bool autoCool = (s == 0? false:true);
    if (autoCool) {
        AdjustLigtCoolnessByCoolCard();
    }
//    if (withDisplay) {
//        this->DisplayLRImages();
//    } else {
////        ClearWindow();
//    }

//    if (isMarkersProcessingEnabled)
//        this->showIdentifiedMarkers();
    if (isXPointsProcessingEnabled)
        this->showIdentifiedXPoints();


    if (this->isCollectingSamples)
        this->collectNewSamples();

    // this->showUnidentifiedVectors();
    return 0;
}

/****************************/
/** */
MTMarker::Marker* Processing::findMarkerInSet(char* name)
{
    MTMarker::Marker* foundMarker;
    for(int i=0; i<this->pMarkers->getTemplateCount(); i++)
    {
        std::string currName;
        this->pMarkers->getTemplateItemName(i, currName);
        if (currName.compare( name)==0)
        {
            foundMarker = new MTMarker::Marker(this->pMarkers->getTemplateItem(i));
            return foundMarker;
        }
        // TODO:verify this
        else
            return NULL;
    }
    return NULL;
}

/****************************/
/** */
void Processing::collectNewSamples()
{
//    static char buffer[255];
//    MTCollection::Collection* col = new MTCollection::Collection( this->pMarkers->unidentifiedVectors(this->pCurrCam) );
//    if (col->count() == 2 )
//    {
//        this->collectingStatus->label("Collecting samples");
//        this->sampleVectors.push_back(col);
//        this->m_collectedSampleFrames++;
//        // Additional facets
//        if (this->isAdditionalFacetAdding)
//        {
//            MTCollection::Collection* identifiedFacetsCol = new MTCollection::Collection(this->pCurrMarker->identifiedFacets(NULL));
//            if (identifiedFacetsCol->count() > 0)
//            {
//                // Also compute and save the xform of facet1 to sensor
//                if (this->pCurrMarker->marker2CameraXf(this->pCurrCam->Handle()) != (Xform3D*)NULL)
//                    this->facet1ToCameraXfs.push_back(this->pCurrMarker->marker2CameraXf(this->pCurrCam->Handle()));
//                else // Seen by a camera not registered with this one
//                {
//                    this->collectingStatus->label("Cannot sample: unregistered camera");
//                    this->sampleVectors.pop_back();
//                    this->m_collectedSampleFrames--;
//                }
//            }
//            else // Not seeing a known facet
//            {
//                this->collectingStatus->label("Cannot sample: no known facet!");
//                this->sampleVectors.pop_back();
//                this->m_collectedSampleFrames--;
//            }
//            delete identifiedFacetsCol;
//        }
//        sprintf(buffer, "Collected: %d\n", this->m_collectedSampleFrames);
//        this->collectingStatus->label(buffer);
//    }
//    else if(col->count() < 2) {
//        this->collectingStatus->label("No new facet detected.");
//    } else if(col->count() > 2) {
//        sprintf(buffer, "More than 2 vectors detected [%d].\n", col->count());
//        this->collectingStatus->label(buffer);
//    }
    //delete col;
}


/****************************/
double Processing::findDistance(double* v1, double* v2)
{
    double acc = 0.0;
    for (int i=0; i< 3; i++)
        acc = acc + ( (v1[i] - v2[i]) * (v1[i] - v2[i]) );
    return sqrt(acc);
}

/****************************/
double Processing::dotProductVectors(double* v1, double* v2)
{
    double result = 0;
    for (int i=0; i<3; i++)
        result += v1[i]*v2[i];
    return result;
}

void Processing::AdjustLigtCoolnessByCoolCard()
{
    MTCollection::Collection* markersCollection = new MTCollection::Collection(this->pMarkers->identifiedMarkers(this->pCurrCam));
    if (markersCollection->count() == 0) {
        delete markersCollection;
        return;
    }
    int markerNum = 1;
    MTMarker::Marker* m;

    for (markerNum = 1; markerNum <= markersCollection->count(); markerNum++)
    {
        m = new MTMarker::Marker(markersCollection->itemI(markerNum));
        if (m->wasIdentified(this->pCurrCam) )
        {
           if ( strncmp( m->getName(),"COOL",4 ) == 0 ||
            ( strncmp( m->getName(),"cool",4 ) == 0) ||
            ( strncmp( m->getName(),"Cool",4 ) == 0)) {
              MTCollection::Collection* facetsCollection = new MTCollection::Collection(m->identifiedFacets(this->pCurrCam));
              for (int facetNum = 1; facetNum <= facetsCollection->count(); facetNum++)
              {
                  Facet* f = new Facet(facetsCollection->itemI(facetNum));
                  if (facetNum == 1) {
                    vector<Vector *> ColorVector;
                    ColorVector = (f->IdentifiedVectors());
                    if ( ColorVector[0] != NULL) {
                        this->pPers->setSection ("General");
                        this->pCurrCam->AdjustCoolnessFromColorVector(ColorVector[0]->Handle());
                        this->pPers->saveDouble("LightCoolness",this->pCurrCam->getLightCoolness());
                    }
                    delete ColorVector[0];
                    delete ColorVector[1];
                  }
                  delete f;
              }
              delete facetsCollection;
           }
        }
        free(m);
    }
    delete markersCollection;


}

void Processing::showIdentifiedXPoints()
{
    MTCollection::Collection* xpointsCollection = new MTCollection::Collection(this->pXPoints->detectedXPoints(this->pCurrCam));

    if (xpointsCollection->count() == 0) {
        delete xpointsCollection;
        return;
    }

    double x[3], y[3];
    double x3,y3,z3;
    int XPNum=1;
    MTXPoint* XP;
    double radius = 5;
    // here we need the left side presentation: coordinates in sensor space, distances etc
    Xform3D* Marker2CurrCameraXf = NULL;
    if(this->isShowingPositions)
    {
        for (XPNum = 1; XPNum <= xpointsCollection->count(); XPNum++)
        {
            XP = new MTXPoint(xpointsCollection->itemI(XPNum));
            XP->Position2D(&x[0], &y[0], &x[1], &y[1], &x[2], &y[2]);
            XP->Position3D(&x3, &y3, &z3);
            XP->setIndex(XPNum);

            drawCircle(0, x[0], y[0], radius, 1.0, 0, 0, 0xFFFF);
        }
    }

    char s[100];
    sprintf(s, "%d", xpointsCollection->count());
    strcat(s, " XPs are detected by Current Camera");
    this->drawText(s, 10/(this->isShowingHalfSize ? 0.5 : 1), 40/(this->isShowingHalfSize ? 0.5 : 1));

}

void Processing::drawLine(int side, float x1, float y1, float x2, float y2, float r, float g, float b, int stipple)
{
//if (useOpenGL) {
//#ifdef OPENGL
//  int xoffset, yoffset;

//  if (side == 1)
//	xoffset = pCurrCam->getXRes() * (this->isShowingHalfSize ? 0.5 : 1);
//  else
//	xoffset = 0;

//  yoffset = pCurrCam->getYRes()*(this->isShowingHalfSize ? 0.5 : 1);
//  gl_start();
//  glPushMatrix();
//  glMatrixMode(GL_MODELVIEW );
//  glColor3f(r,g,b);
//  glLineWidth (2);
//  glPushAttrib (GL_LINE_BIT);
//  glLineStipple (3, stipple);
//  glBegin (GL_LINE_STRIP);
//  glVertex2d (xoffset + x1*(this->isShowingHalfSize ? 0.5 : 1), yoffset - y1*(this->isShowingHalfSize ? 0.5 : 1));
//  glVertex2d (xoffset + x2*(this->isShowingHalfSize ? 0.5 : 1), yoffset - y2*(this->isShowingHalfSize ? 0.5 : 1));
//  glEnd ();
//  glPopAttrib ();
//  glPopMatrix();
//  glFinish();
//#endif
//} else {

//	float xoffset, yoffset;

//	if (side == 1)
//		xoffset = pCurrCam->getXRes() * (this->isShowingHalfSize ? 0.5 : 1);
//	else
//		xoffset = 0;
//	yoffset = MENU_HEIGHT;
//	fl_color(fl_rgb_color(r*255, g*255, b*255));
//	fl_line(xoffset + x1*(this->isShowingHalfSize ? 0.5 : 1), yoffset + y1*(this->isShowingHalfSize ? 0.5 : 1), xoffset + x2*(this->isShowingHalfSize ? 0.5 : 1), yoffset + y2*(this->isShowingHalfSize ? 0.5 : 1)) ;

//}
}

void Processing::drawCircle(int side, float x, float y, float radius, float r, float g, float b, int stipple)
{
//if (useOpenGL) {
//#ifdef OPENGL
//	int xoffset, yoffset;

//	if (side == 1)
//		xoffset = pCurrCam->getXRes() * (this->isShowingHalfSize ? 0.5 : 1);
//	else
//		xoffset = 0;
//  yoffset = pCurrCam->getYRes()*(this->isShowingHalfSize ? 0.5 : 1);
//  gl_start();
//  glPushMatrix();
//  glColor3f(r,g,b);
//  glLineWidth (2);
//  glPushAttrib (GL_LINE_BIT);
//  glLineStipple (3, stipple);
//  glBegin(GL_POLYGON);
//	for( double ang=0; ang <= 2*PI; ang += 0.1)
//	{
//		double c = cos(ang);
//		double s = sin(ang);
//		glVertex2d( xoffset + x * (this->isShowingHalfSize ? 0.5 : 1) + radius * c,
//                     yoffset - y *(this->isShowingHalfSize ? 0.5 : 1) + radius * s);
//	}
//  glEnd();
//  glPopAttrib ();
//  glPopMatrix();
//  glFinish();
//#endif
//} else {
//	int xoffset, yoffset;

//	if (side == 1)
//		xoffset = pCurrCam->getXRes() * (this->isShowingHalfSize ? 0.5 : 1);
//	else
//		xoffset = 0;
//	yoffset = MENU_HEIGHT;
//	fl_color(fl_rgb_color(r*255, g*255, b*255));
//	fl_circle( x * (this->isShowingHalfSize ? 0.5 : 1) + xoffset,  y*(this->isShowingHalfSize ? 0.5 : 1)+ yoffset,  (float)radius);

//}
}

void Processing::drawText( char* text, int x, int y)
{
//if (useOpenGL) {
//#ifdef __APPLE__
//    window->make_current();
//    gl_start();
//	glPushMatrix();

//    glRasterPos2f(x * (this->isShowingHalfSize ? 0.5 : 1),  480 - y * (this->isShowingHalfSize ? 0.5 : 1));
//    const char * message = (const char*)text;
//    while (*message)
//		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *message++);

//    glColor3f(0.3, 0.1, 1.0);

//	glEnd ();
//    glPopAttrib ();
//    glPopMatrix();
//    glFinish();
//#endif

//    } else {

//	window->make_current();
//	fl_font(FL_TIMES /*| FL_BOLD*/ , 20);

//	fl_color(fl_rgb_color(15, 15, 255));
//	fl_draw((const char*)(text), x * (this->isShowingHalfSize ? 0.5 : 1),  y * (this->isShowingHalfSize ? 0.5 : 1));

//    }
}
