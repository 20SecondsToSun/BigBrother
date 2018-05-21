#pragma once
#include "ofMain.h"

namespace bbrother
{
	typedef ofPtr<class Tracker> TrackerPtr;

	enum class TrackerError
	{
		None,
		TrackerOff
	};

	class Tracker
	{
	public:
		Tracker();

		ofEvent<void> humanDetect;
		ofEvent<void> humanLost;
		ofEvent<void> trackerError;

		virtual void update() = 0;
		virtual void draw() = 0;	

		virtual void start() = 0;
		virtual void stop() = 0;		

		virtual ~Tracker();

	protected:

	};
}

