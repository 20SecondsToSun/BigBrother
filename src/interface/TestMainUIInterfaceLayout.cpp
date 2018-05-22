#include "TestMainUIInterfaceLayout.h"
#include <random>

using namespace bbrother;

TestMainUIInterfaceLayout::TestMainUIInterfaceLayout()
{
	ofLog(ofLogLevel::OF_LOG_NOTICE, "IFish InterfaceLayout init");
	
	screen1btn = ofPtr<ofxDatGuiButton>(new ofxDatGuiButton("Detect"));
	screen1btn->onButtonEvent(this, &TestMainUIInterfaceLayout::screen1ButtonClicked);
	components.push_back(screen1btn);

	screen2btn = ofPtr<ofxDatGuiButton>(new ofxDatGuiButton("Recognise"));
	screen2btn->onButtonEvent(this, &TestMainUIInterfaceLayout::screen2ButtonClicked);
	components.push_back(screen2btn);

	//screen3btn = ofPtr<ofxDatGuiButton>(new ofxDatGuiButton("Recognise"));
	//screen3btn->onButtonEvent(this, &TestMainUIInterfaceLayout::screen3ButtonClicked);
	//components.push_back(screen3btn);

	//default align
	setPosition(ofPoint(100, 40));
	std::srand(0);
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
	int a = std::rand();
	ofImage pic;
	std::string name;
	switch (a%6) {
	case 0:
		pic.load("images/photo0.jpg");
		name = "";
		break;
	case 1:
		pic.load("images/photo1.jpg");
		name = "";
		break;
	case 2:
		pic.load("images/photo2.jpg");
		name = "";
		break;
	case 3:
		pic.load("images/photo3.jpg");
		name = "";
		break;
	case 4:
		pic.load("images/photo4.jpg");
		name = "";
		break;
	case 5:
		pic.load("images/photo5.jpg");
		name = "";
	case 6:
		pic.load("images/photo6.jpg");
		name = "";
		break;
	default:
		break;
	}
	PersonPtr newPer(new Person(a, pic));
	newPer->faceData.name = name;

	MyEvent myevent(InterfaceEventType::NewPersonAppear, newPer);

	ofNotifyEvent(InterfaceEvent, myevent);
}

void TestMainUIInterfaceLayout::screen2ButtonClicked(ofxDatGuiButtonEvent event)
{
	auto type = InterfaceEventType::PersonRecognized;
	//ofNotifyEvent(InterfaceEvent, type);
}

void TestMainUIInterfaceLayout::screen3ButtonClicked(ofxDatGuiButtonEvent event)
{
	auto type = InterfaceEventType::NewPersonAppear;
	//ofNotifyEvent(InterfaceEvent, type);
}

TestMainUIInterfaceLayout::~TestMainUIInterfaceLayout()
{

}
