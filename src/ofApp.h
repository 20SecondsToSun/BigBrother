#pragma once
#include "ofMain.h"
#include "tracker/Tracker.h"
#include "config/Config.h"
#include "ui/ScreenController.h"
#include "debugUI/TestInterfaceLayout.h"
#include "facedetector/controller/FaceController.h"
#include "family/FamilyBaseRequestHandler.h"
#include "person/Person.h"
#include "person/PersonController.h"

#define DEBUG_VERSION//

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void windowResized( int w, int h );

private:
	bbrother::ConfigPtr config;
	bbrother::TrackerPtr tracker;
	bbrother::FaceDetectorPtr facedetector;
	bbrother::ScreenControllerPtr screenController;
	bbrother::FaceControllerPtr faceController;
	bbrother::PersonControllerPtr personController;
	

#ifdef DEBUG_VERSION
	bbrother::TestInterfaceLayoutPtr testKinectInterfaceLayout;
	bbrother::TestInterfaceLayoutPtr testMainUIInterfaceLayout;
#endif

	void onConfigLoadComplete();
	void onInterfaceEvent(bbrother::InterfaceEventType& Event);

	void onNewPersonAppear(bbrother::Tracker::TrackerPerson& trackerPerson);

	void onPersonFaceDetect(bbrother::PersonPtr& person);
	void onPersonFaceNotDetect(bbrother::PersonPtr& person);
	void onPersonFoundInFaceSet(bbrother::PersonPtr& person);
	void onPersonNotFoundInFaceSet(bbrother::PersonPtr& person);
	void onPersonFoundInFamilyBase(bbrother::PersonPtr& person);
	void onPersonNotFoundInFamilyBase(bbrother::PersonPtr& person);
	void onFaceServiceError();
};