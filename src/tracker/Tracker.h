#pragma once
#include "ofMain.h"
#include "../config/Config.h"

namespace bbrother
{
	typedef ofPtr<class Tracker> TrackerPtr;

	enum class TrackerError
	{
		None,
		TrackerOff
	};

	struct TrackerPerson
	{
		ofImage image;
		ofRectangle rect;
	};

	class Tracker
	{
	public:
		Tracker();

		ofEvent<TrackerPerson> newPersonAppear;
		ofEvent<void> humanLost;
		ofEvent<TrackerError> trackerError;

		virtual void update() = 0;
		virtual void draw() = 0;	

		virtual void init(ConfigPtr config) = 0;

		virtual void start() = 0;
		virtual void stop() = 0;		

		virtual ~Tracker();

	protected:

	};
}

