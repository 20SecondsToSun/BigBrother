#include "TestFacePlusPlusInterfaceLayout.h"

using namespace bbrother;

void TestFacePlusPlusInterfaceLayout::Open() {
	ofFileDialogResult openFileResult = ofSystemLoadDialog( "Select a jpg or png" );

	if( openFileResult.bSuccess ) {
		ofLog( ofLogLevel::OF_LOG_NOTICE, "User selected a file" );
		face_detector->ProcessImage(openFileResult.filePath );

	} else {
		ofLog( ofLogLevel::OF_LOG_NOTICE, "User hit cancel" );
	}
}

TestFacePlusPlusInterfaceLayout::TestFacePlusPlusInterfaceLayout()
{
	ofLog( ofLogLevel::OF_LOG_NOTICE, "Face++ TestInterfaceLayout init" );

	screen1btn = ofPtr<ofxDatGuiButton>( new ofxDatGuiButton( "Open photo" ) );
	screen1btn->onButtonEvent( this, &TestFacePlusPlusInterfaceLayout::screen1ButtonClicked );
	components.push_back( screen1btn );

	status_label = ofPtr<ofxDatGuiLabel>(new ofxDatGuiLabel( "status" ));
	components.push_back( status_label );

	face_detector = ofPtr<FaceDetector>(new FacePlusPlusDetector());
	face_detector->init(config);

	setPosition( ofPoint( 100, 40 ) );
	std::cout << "const";
	ofAddListener( face_detector->status_event, this, &TestFacePlusPlusInterfaceLayout::statusChanged );
	std::cout << "added";
}

void TestFacePlusPlusInterfaceLayout::setConfig( ConfigPtr config_ ) {
	config = config_;
}


void TestFacePlusPlusInterfaceLayout::statusChanged(FaceDetector::Status& status) {
	switch( status ) {
	case FaceDetector::Status::Detect:
		status_label->setLabel( "Detect" );
		break;
	case FaceDetector::Status::NotDetect:
		status_label->setLabel( "Not Detect" );
		break;
	case FaceDetector::Status::Process:
		status_label->setLabel( "Process" );
		break;
	case FaceDetector::Status::WaitForPhoto:
		status_label->setLabel( "Wait For Photo" );
		break;
	default:
		break;
	}
}

void TestFacePlusPlusInterfaceLayout::update()
{
	TestInterfaceLayout::update();
}

void TestFacePlusPlusInterfaceLayout::draw()
{
	TestInterfaceLayout::draw();
}

void TestFacePlusPlusInterfaceLayout::screen1ButtonClicked( ofxDatGuiButtonEvent event )
{
	Open();
}