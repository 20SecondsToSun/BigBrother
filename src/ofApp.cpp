#include "ofApp.h"
#include "config/Config.h"
#include "debugUI/TestKinectInterfaceLayout.h"
#include "debugUI/TestMainUIInterfaceLayout.h"
#include "tracker/KinectTracker.h"
#include "facedetector/faceplusplus/FacePlusPlusDetector.h"
#include "debugUI/TestFacePlusPlusInterfaceLayout.h"

using namespace bbrother;

//--------------------------------------------------------------
void ofApp::setup()
{
	config = ConfigPtr(new Config());
	ofAddListener(config->loadCompleteEvent, this, &ofApp::onConfigLoadComplete);

#ifdef DEBUG_VERSION	
	/*testKinectInterfaceLayout = TestInterfaceLayoutPtr(new TestKinectInterfaceLayout());
	testKinectInterfaceLayout->setPosition(ofPoint(20, 40));
	testKinectInterfaceLayout->setVisibility(true);
	ofAddListener(testKinectInterfaceLayout->InterfaceEvent, this, &ofApp::onInterfaceEvent);
	*/

	//testMainUIInterfaceLayout = TestInterfaceLayoutPtr(new TestMainUIInterfaceLayout());
	//testMainUIInterfaceLayout->setPosition(ofPoint(400, 40));
	//testMainUIInterfaceLayout->setVisibility(true);
	//ofAddListener(testMainUIInterfaceLayout->InterfaceEvent, this, &ofApp::onInterfaceEvent);
	
	testMainUIInterfaceLayout = TestInterfaceLayoutPtr(new TestFacePlusPlusInterfaceLayout());
	testMainUIInterfaceLayout->setPosition(ofPoint(400, 40));
	testMainUIInterfaceLayout->setVisibility(true);
	testMainUIInterfaceLayout->setConfig( config );
	ofAddListener(testMainUIInterfaceLayout->InterfaceEvent, this, &ofApp::onInterfaceEvent);
#endif

	tracker = bbrother::TrackerPtr(new KinectTracker());
	ofAddListener(tracker->newPersonAppear, this, &ofApp::onNewPersonAppear);

	faceController = FaceControllerPtr(new FaceController());
	ofAddListener(faceController->serviceError, this, &ofApp::onFaceServiceError);
	ofAddListener(faceController->personFaceDetect, this, &ofApp::onPersonFaceDetect);
	ofAddListener(faceController->personFaceNotDetect, this, &ofApp::onPersonFaceNotDetect);
	ofAddListener(faceController->personFoundInFaceSet, this, &ofApp::onPersonFoundInFaceSet);
	ofAddListener(faceController->personNotFoundInFaceSet, this, &ofApp::onPersonNotFoundInFaceSet);
	ofAddListener(faceController->personFoundInFamilyBase, this, &ofApp::onPersonFoundInFamilyBase);
	ofAddListener(faceController->personNotFoundInFamilyBase, this, &ofApp::onPersonNotFoundInFamilyBase);
	
	screenController = bbrother::ScreenControllerPtr(new ScreenController());

	//printerWorker = bbrother::PrinterWorkerPtr(new PrinterWorker());	
	//tcpController = TcpControllerPtr(new TcpController());

	config->load();
}

void ofApp::onNewPersonAppear(Tracker::TrackerPerson& trackerPerson)
{
	PersonPtr person = personController->createNewPerson(trackerPerson);
	screenController->newPersonAppear(person);
	faceController->newPersonAppear(person);	
}
//--------------------------------------------------------------

void ofApp::onPersonFaceDetect(PersonPtr& person)
{

}

void ofApp::onPersonFaceNotDetect(PersonPtr& person)
{

}

void ofApp::onPersonFoundInFaceSet(PersonPtr& person)
{

}

void ofApp::onPersonNotFoundInFaceSet(PersonPtr& person)
{

}

void ofApp::onPersonFoundInFamilyBase(PersonPtr& person)
{

}

void ofApp::onPersonNotFoundInFamilyBase(PersonPtr& person)
{

}

void ofApp::onFaceServiceError()
{

}

void ofApp::onConfigLoadComplete()
{
	// entry point....
	ofLog(ofLogLevel::OF_LOG_NOTICE, "Config load complete");

	tracker->init(config);
	faceController->init(config);
	screenController->init(config);	

	ofLog(ofLogLevel::OF_LOG_NOTICE, "Start application...");
}

//--------------------------------------------------------------
void ofApp::onInterfaceEvent(bbrother::InterfaceEventType& Event)
{
	switch (Event)
	{
	case InterfaceEventType::TrackingStart:
		ofLog(ofLogLevel::OF_LOG_NOTICE, "Try kinect starts...");
		break;

	case InterfaceEventType::ShowWaitScreen:
		ofLog(ofLogLevel::OF_LOG_NOTICE, "Show Wait Screen...");
		break;

	//@todo
	//case InterfaceEventType::SelectFile:
		//facedetector->processImage(cast to testMainUIInterfaceLayout->getFilePath)
	//	break;
	}
}

//--------------------------------------------------------------
void ofApp::update()
{
	tracker->update();
	faceController->update();
	screenController->update();	

#ifdef DEBUG_VERSION
	//testKinectInterfaceLayout->update();
	testMainUIInterfaceLayout->update();
#endif
}

//--------------------------------------------------------------
void ofApp::draw()
{
	//tracker->draw();
	//faceController->draw();
	screenController->draw();

#ifdef DEBUG_VERSION
	// on top level
	//testKinectInterfaceLayout->draw();
	testMainUIInterfaceLayout->draw();
#endif
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

