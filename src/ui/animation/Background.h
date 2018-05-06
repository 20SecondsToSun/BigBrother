#pragma once

#include "ofMain.h"

namespace bbrother
{
	typedef ofPtr<class Background> BackgroundPtr;

	class Background
	{
	public:
		Background();

		void update();
		void draw();

		virtual ~Background();
	private:
		
	};
}