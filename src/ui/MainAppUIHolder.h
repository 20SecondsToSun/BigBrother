#pragma once
#include "ofMain.h"
#include "screens/BaseScreen.h"

namespace bbrother
{
	typedef ofPtr<class MainAppUIHolder> MainAppUIHolderPtr;

	enum class ScreenState
	{
		None,
		Wait,
		Detect,
		Result
	};

	class MainAppUIHolder
	{
	public:
		MainAppUIHolder();
		virtual void update();
		virtual void draw();

		virtual ~MainAppUIHolder();

	private:
		BaseScreenPtr currentScreen;
	};
}

