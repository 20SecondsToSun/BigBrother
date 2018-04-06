#pragma once
#include "ofMain.h"
#include "Tracker.h"

namespace bbrother
{
	typedef ofPtr<class KinectTracker> KinectTrackerPtr;

	class KinectTracker: public Tracker
	{
	public:
		KinectTracker();
		virtual void update() override;
		virtual void draw() override;	

		virtual void init(ConfigPtr config) override;


		virtual void start() override;
		virtual void stop() override;

		virtual ~KinectTracker();
	};
}

