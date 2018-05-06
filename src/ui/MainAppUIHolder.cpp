#include "MainAppUIHolder.h"
#include "ofMain.h"
#include "../interface/TestMainUIInterfaceLayout.h"

using namespace bbrother;

MainAppUIHolder::MainAppUIHolder()
{
	background = BackgroundPtr(new Background());
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

MainAppUIHolder::~MainAppUIHolder()
{

}

void MainAppUIHolder::onInterfaceEvent(bbrother::InterfaceEventType& Event)
{
	switch (Event)
	{
	case InterfaceEventType::NewPersonAppear:
		screenController->newPersonAppear(PersonPtr(new Person(idadd++)));
		break;

	case InterfaceEventType::PersonRecognized:
		screenController->personRecognized(PersonPtr(new Person(iddel++)));
		break;
	}
}
