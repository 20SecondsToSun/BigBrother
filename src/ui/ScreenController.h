#pragma once
#include "ofMain.h"
#include "screens/BaseScreen.h"
#include "../person/Person.h"
#include "../config/Config.h"

namespace bbrother
{
	typedef ofPtr<class ScreenController> ScreenControllerPtr;

	enum class ScreenState
	{
		None,
		Wait,
		Detect,
		Result
	};

	class ScreenController
	{
	public:
		ScreenController();
		virtual void update();
		virtual void draw();

		virtual void init(ConfigPtr config);

		void newPersonAppear(PersonPtr person);
		virtual ~ScreenController();

	private:
		BaseScreenPtr currentScreen;
	};
}

