#include "TestMainUIInterfaceLayout.h"

using namespace bbrother;

TestMainUIInterfaceLayout::TestMainUIInterfaceLayout()
{
	ofLog(ofLogLevel::OF_LOG_NOTICE, "IFish InterfaceLayout init");
	
	screen1btn = ofPtr<ofxDatGuiButton>(new ofxDatGuiButton("Wait Screen"));
	screen1btn->onButtonEvent(this, &TestMainUIInterfaceLayout::screen1ButtonClicked);
	components.push_back(screen1btn);

	screen2btn = ofPtr<ofxDatGuiButton>(new ofxDatGuiButton("Detect Screen"));
	screen2btn->onButtonEvent(this, &TestMainUIInterfaceLayout::screen2ButtonClicked);
	components.push_back(screen2btn);

	screen3btn = ofPtr<ofxDatGuiButton>(new ofxDatGuiButton("Result Screen"));
	screen3btn->onButtonEvent(this, &TestMainUIInterfaceLayout::screen3ButtonClicked);
	components.push_back(screen3btn);

	//default align
	setPosition(ofPoint(100, 40));
}

void TestMainUIInterfaceLayout::update()
{
	TestInterfaceLayout::update();	
}

void TestMainUIInterfaceLayout::draw()
{
	TestInterfaceLayout::draw();
}

void TestMainUIInterfaceLayout::screen1ButtonClicked(ofxDatGuiButtonEvent event)
{
	auto type = InterfaceEventType::ShowWaitScreen;
	ofNotifyEvent(InterfaceEvent, type);
}

void TestMainUIInterfaceLayout::screen2ButtonClicked(ofxDatGuiButtonEvent event)
{

}

void TestMainUIInterfaceLayout::screen3ButtonClicked(ofxDatGuiButtonEvent event)
{
	
}

TestMainUIInterfaceLayout::~TestMainUIInterfaceLayout()
{

}
