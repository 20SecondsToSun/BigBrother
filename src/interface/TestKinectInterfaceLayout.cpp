#include "TestKinectInterfaceLayout.h"

using namespace bbrother;

TestKinectInterfaceLayout::TestKinectInterfaceLayout()
{
	ofLog(ofLogLevel::OF_LOG_NOTICE, "BigBrother InterfaceLayout init");
	
	kinectStartButton = ofPtr<ofxDatGuiButton>(new ofxDatGuiButton("Kinect Start"));
	kinectStartButton->onButtonEvent(this, &TestKinectInterfaceLayout::kinectStartButtonClicked);	
	components.push_back(kinectStartButton);

	kinectStopButton = ofPtr<ofxDatGuiButton>(new ofxDatGuiButton("Kinect Stop"));
	kinectStopButton->onButtonEvent(this, &TestKinectInterfaceLayout::kinectStopButtonClicked);
	kinectStopButton->setEnabled(false);
	components.push_back(kinectStopButton);

	kinectShowFrames = ofPtr<ofxDatGuiButton>(new ofxDatGuiButton("Kinect Show Frames"));
	kinectShowFrames->onButtonEvent(this, &TestKinectInterfaceLayout::kinectShowFramesButtonClicked);
	components.push_back(kinectShowFrames);

	peopleTrackedText = ofPtr<ofxDatGuiLabel>(new ofxDatGuiLabel("People tracked: 0"));
	components.push_back(peopleTrackedText);

	//default align
	setPosition(ofPoint(20, 40));
}

void TestKinectInterfaceLayout::update()
{
	TestInterfaceLayout::update();	
}

void TestKinectInterfaceLayout::draw()
{
	TestInterfaceLayout::draw();
}

void TestKinectInterfaceLayout::kinectStartButtonClicked(ofxDatGuiButtonEvent event)
{
	auto type = InterfaceEventType::TrackingStart;
	//ofNotifyEvent(InterfaceEvent, type);
}

void TestKinectInterfaceLayout::kinectStopButtonClicked(ofxDatGuiButtonEvent event)
{
	auto type = InterfaceEventType::TrackingStop;
	//ofNotifyEvent(InterfaceEvent, type);
}

void TestKinectInterfaceLayout::kinectShowFramesButtonClicked(ofxDatGuiButtonEvent event)
{
	
}

TestKinectInterfaceLayout::~TestKinectInterfaceLayout()
{

}
