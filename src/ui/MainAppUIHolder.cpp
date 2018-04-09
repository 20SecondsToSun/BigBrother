#include "MainAppUIHolder.h"
#include "ofMain.h"
#include "../interface/TestMainUIInterfaceLayout.h"

using namespace bbrother;

MainAppUIHolder::MainAppUIHolder()
{
	background = CloudPtr(new Cloud());
	screenController = ScreenControllerPtr(new ScreenController());

	ofLog(ofLogLevel::OF_LOG_NOTICE, "MainAppUIHolder init");
}

void MainAppUIHolder::update()
{
	background->update();
	screenController->update();
}

void MainAppUIHolder::draw()
{
	background->draw();
	screenController->draw();
}

void MainAppUIHolder::setter(ScreenState _state)
{
	
}

MainAppUIHolder::~MainAppUIHolder()
{

}

void MainAppUIHolder::onInterfaceEvent(bbrother::InterfaceEventType& Event)
{
	switch (Event)
	{
	case InterfaceEventType::ShowWaitScreen:
		break;

	case InterfaceEventType::ShowDetectScreen:
		screenController->newPersonAppear(PersonPtr(new Person(idadd++)));
		break;

	case InterfaceEventType::ShowResultScreen:
		screenController->personRecognized(PersonPtr(new Person(iddel++)));
		break;
	}
}
