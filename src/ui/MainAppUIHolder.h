#pragma once
#include "ofMain.h"
#include "ScreenController.h"
#include "animation\Background.h"
#include "../interface/TestInterfaceLayout.h"

namespace bbrother
{
	typedef ofPtr<class MainAppUIHolder> MainAppUIHolderPtr;

	class MainAppUIHolder
	{
	public:
		MainAppUIHolder();

		virtual void update();
		virtual void draw();

		virtual ~MainAppUIHolder();

		void onInterfaceEvent(InterfaceEventType& Event);

	private:
		BackgroundPtr background;
		ScreenControllerPtr screenController;

		//debug
		int idadd = 0;
		int iddel = 0;
	};
}

