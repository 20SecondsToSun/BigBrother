#include "ofApp.h"
#include "config/Config.h"
#include "interface/TestKinectInterfaceLayout.h"
#include "interface/TestMainUIInterfaceLayout.h"
#include "tracker/KinectTracker.h"
#include "facedetector/faceplusplus/FacePlusPlusDetector.h"
#include "interface/TestFacePlusPlusInterfaceLayout.h"
#include "facedetector/faceplusplus/FaceDataBaseHandler.h"
#include "facedetector/faceplusplus/FaceSetHandler.h"

using namespace bbrother;

//--------------------------------------------------------------
void ofApp::setup()
{
	config = ConfigPtr(new Config());
	ofAddListener(config->loadCompleteEvent, this, &ofApp::onConfigLoadComplete);

#ifdef DEBUG_VERSION	

	testMainUIInterfaceLayout = TestInterfaceLayoutPtr(new TestFacePlusPlusInterfaceLayout());
	testMainUIInterfaceLayout->setPosition(ofPoint(400, 40));
	testMainUIInterfaceLayout->setVisibility(true);
	testMainUIInterfaceLayout->setConfig( config );
	ofAddListener(testMainUIInterfaceLayout->InterfaceEvent, this, &ofApp::onInterfaceEvent);

	TestFacePlusPlusInterfaceLayout* testPointer = dynamic_cast<TestFacePlusPlusInterfaceLayout*>( testMainUIInterfaceLayout.get() );
	FaceDataBaseHandler* handler_db = new FaceDataBaseHandler();
	FaceSetHandler* handler_face_set = new FaceSetHandler();

	/*Face* res = testPointer->face_detector->ProcessImage( "c:\\demo1.jpg" );
	int id = handler_db->CreateUser( "Jolie", res->getToken() );
	testPointer->face_detector->AddUserId( id, res->getToken() );
	handler_face_set->AddFaces( res->getToken() );

	res = testPointer->face_detector->ProcessImage( "c:\\demo2.jpg" );
	handler_face_set->AddFaces( res->getToken() );
	id = handler_db->CreateUser( "Ann", res->getToken() );
	testPointer->face_detector->AddUserId( id, res->getToken() );

	res = testPointer->face_detector->ProcessImage( "c:\\demo3.jpg" );
	id = handler_db->CreateUser( "Don't remember who", res->getToken() );
	testPointer->face_detector->AddUserId( id, res->getToken() );
	handler_face_set->AddFaces( res->getToken() );*/

	handler_db->GetAll();

	Face* res = testPointer->face_detector->ProcessImage( "c:\\demoSearch1.jpg" );
	int user_id = handler_face_set->Search( res );
	if( user_id != -1 ) {
		std::cout << std::endl << "FOUND" << std::endl;
		std::cout << user_id << std::endl;;
	} else {
		std::cout << std::endl << "NOT FOUND" << std::endl;
	}

#endif

	//tracker = bbrother::TrackerPtr(new KinectTracker());
	facedetector = bbrother::FaceDetectorPtr(new FacePlusPlusDetector());
	//mainUI = bbrother::MainAppUIHolderPtr(new MainAppUIHolder());

	//printerWorker = bbrother::PrinterWorkerPtr(new PrinterWorker());	
	//tcpController = TcpControllerPtr(new TcpController());

	config->load();
}

//--------------------------------------------------------------
void ofApp::onConfigLoadComplete()
{
	ofLog(ofLogLevel::OF_LOG_NOTICE, "Config load complete");

	facedetector->init(config);

	ofLog(ofLogLevel::OF_LOG_NOTICE, "Start application...");
}

//--------------------------------------------------------------
void ofApp::onInterfaceEvent(bbrother::InterfaceEventType& Event)
{
	/* switch (Event)
	{
	case InterfaceEventType::TrackingStart:
		ofLog(ofLogLevel::OF_LOG_NOTICE, "Try kinect starts...");
		break;

	case InterfaceEventType::ShowWaitScreen:
		ofLog(ofLogLevel::OF_LOG_NOTICE, "Show Wait Screen...");
		break;
	} */
}

//--------------------------------------------------------------
void ofApp::update()
{
	//tracker->update();
	//mainUI->update();

#ifdef DEBUG_VERSION
	//testKinectInterfaceLayout->update();
	testMainUIInterfaceLayout->update();
#endif
}

//--------------------------------------------------------------
void ofApp::draw()
{
	//tracker->draw();
	//mainUI->draw();

#ifdef DEBUG_VERSION
	// on top level
	//testKinectInterfaceLayout->draw();
	testMainUIInterfaceLayout->draw();
#endif
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

