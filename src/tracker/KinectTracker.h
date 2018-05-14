#pragma once
#include "ofMain.h"
#include "Tracker.h"
#include "ofxKinectForWindows2.h"

namespace bbrother
{
	typedef ofPtr<class KinectTracker> KinectTrackerPtr;

	class KinectTracker: public Tracker
	{
	public:
		KinectTracker();
		virtual void update() override;
		virtual void draw() override;			

		virtual void start() override;
		virtual void stop() override;

		virtual ~KinectTracker();
		virtual void init(ConfigPtr config) override;

		ofImage cropFrame(const ofImage& source, const ofRectangle& sorect);

	private:
		int DepthWidth = 512;
		int DepthHeight = 424;

		int ColorWidth = 1920;
		int ColorHeight = 1080;
		int DepthSize = DepthWidth * DepthHeight;

		bool running = false;

		ofxKFW2::Device kinect;
		ICoordinateMapper* coordinateMapper;

		ofImage bodyIndexImg, foregroundImg;
		vector<ofVec2f> colorCoords;
		int bodiesTrackedCount;
		bool haveAllStreams;

		ofFbo personFbo;

		bool testOneDraw = false;
	};
}

