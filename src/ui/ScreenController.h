#pragma once
#include "ofMain.h"
#include "screens/BaseScreen.h"
#include "../person/Person.h"
#include <map>


namespace bbrother
{
	typedef ofPtr<class ScreenController> ScreenControllerPtr;

	enum class ScreenState
	{
		Wait,
		Work,
		Errror
	};

	class ScreenController
	{
	public:
		ScreenController();

		ofEvent<void> loadCompleteEvent;
		ofEvent<void> loadErrorEvent;

		virtual void update();
		virtual void draw();

		void newPersonAppear(PersonPtr person);
		void personRecognized(PersonPtr person);

		void setCurrentState(ScreenState state);
		void setWaitScreen();
		void setWorkScreen();

		void toWaitScreen();
		void toWorkScreen();

		virtual ~ScreenController();

	private:
		ScreenState currentState;
		BaseScreenPtr currentScreen;
		std::map<ScreenState, BaseScreenPtr> screens;
	};
}