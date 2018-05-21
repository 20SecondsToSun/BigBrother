#include "KinectTracker.h"

using namespace bbrother;

KinectTracker::KinectTracker()
{
	ofLog(ofLogLevel::OF_LOG_NOTICE, "Kinect Tracker init");

	//camera image handler
	//opencv analyzer
}

void KinectTracker::init(ConfigPtr config)
{
	DepthWidth = 512;
	DepthHeight = 424;

	ColorWidth = 1920;
	ColorHeight = 1080;

	DepthSize = DepthWidth * DepthHeight;
}

void KinectTracker::start()
{
	bodiesTrackedCount = 0;
	haveAllStreams = false;

	kinect.open();
	kinect.initDepthSource();
	kinect.initColorSource();
	kinect.initInfraredSource();
	kinect.initBodySource();
	kinect.initBodyIndexSource();

	if (kinect.getSensor()->get_CoordinateMapper(&coordinateMapper) < 0)
	{
		ofLogError() << "Could not acquire CoordinateMapper!";
	}

	bodyIndexImg.allocate(DepthWidth, DepthHeight, OF_IMAGE_COLOR);
	foregroundImg.allocate(ColorWidth, ColorHeight, OF_IMAGE_COLOR);
	colorCoords.resize(DepthWidth * DepthHeight);

	personFbo.allocate(ColorWidth, ColorHeight, GL_RGBA);

	running = true;
}

void KinectTracker::update()
{
	if (!running)
	{
		return;
	}

	kinect.update();

	// Get pixel data
	auto& depthPix = kinect.getDepthSource()->getPixels();
	auto& bodyIndexPix = kinect.getBodyIndexSource()->getPixels();
	auto& colorPix = kinect.getColorSource()->getPixels();

	haveAllStreams = (depthPix.size() && bodyIndexPix.size() && colorPix.size());
	if (!haveAllStreams)
	{
		return;
	}


	bodiesTrackedCount = 0;
	auto& bodies = kinect.getBodySource()->getBodies();
	for (auto& body : bodies)
	{
		if (body.tracked)
		{
			bodiesTrackedCount++;
		}
	}

	coordinateMapper->MapDepthFrameToColorSpace(DepthSize, (UINT16*)depthPix.getPixels(), DepthSize, (ColorSpacePoint*)colorCoords.data());

	// Loop through the depth image
	for (int y = 0; y < DepthHeight; ++y)
	{
		for (int x = 0; x < DepthWidth; ++x)
		{
			int index = (y * DepthWidth) + x;
			//bodyIndexImg.setColor(x, y, ofColor::white);
			foregroundImg.setColor(x, y, ofColor::white);

			float val = bodyIndexPix[index];
			if (val >= bodies.size())
			{
				continue;
			}

			//ofColor c = ofColor::fromHsb(val * 255 / bodies.size(), 200, 255);
			//bodyIndexImg.setColor(x, y, c);

			// For a given (x,y) in the depth image, lets look up where that point would be
			// in the color image
			ofVec2f mappedCoord = colorCoords[index];

			// Mapped x/y coordinates in the color can come out as floats since it's not a 1:1 mapping
			// between depth <-> color spaces i.e. a pixel at (100, 100) in the depth image could map
			// to (405.84637, 238.13828) in color space
			// So round the x/y values down to ints so that we can look up the nearest pixel
			mappedCoord.x = floor(mappedCoord.x);
			mappedCoord.y = floor(mappedCoord.y);

			// Make sure it's within some sane bounds, and skip it otherwise
			if (mappedCoord.x < 0 || mappedCoord.y < 0 || mappedCoord.x >= ColorWidth || mappedCoord.y >= ColorHeight)
			{
				continue;
			}
			foregroundImg.setColor(x, y, colorPix.getColor(mappedCoord.x, mappedCoord.y));
		}
	}



	bodyIndexImg.update();
	ofRectangle rec(0, 0, bodyIndexImg.getWidth(), bodyIndexImg.getHeight());
	ofImage resImg = cropFrame(bodyIndexImg, rec);
	sendImage(resImg);
	//resImg.saveImage("C:\Users\maxim\Pictures\image.png");
	foregroundImg.update();
}

void KinectTracker::draw()
{
	if (!running)
	{
		return;
	}

	bodyIndexImg.draw(0, 0);

	auto& bodies = kinect.getBodySource()->getBodies();
	for (auto& body : bodies)
	{
		if (body.tracked)
		{
			bodiesTrackedCount++;

			ofPushStyle();
			{
				ofColor color(200, 100, 100);
				int index = 0;
				ofSetColor(color);
				for (const auto & joint : body.joints)
				{
					ofDrawCircle(joint.second.getPositionInDepthMap(), 10);
				}
			}
			ofPopStyle();

			/*if (!testOneDraw)
			{
			personFbo.begin();
			ofSetColor(255, 255, 255, 255);
			foregroundImg.draw(0, 0);
			personFbo.end();
			/*auto screenShot = personFbo.getTexture();
			ofPixels pixels;
			screenShot.readToPixels(pixels);
			ofImage image;
			image.setFromPixels(pixels);
			image.save("file.png");
			testOneDraw = true;

			}		*/
		}
	}

	//kinect.getDepthSource()->draw(0, 0, DepthWidth, DepthHeight);  // note that the depth texture is RAW so may appear dark

	//																   // Color is at 1920x1080 instead of 512x424 so we should fix aspect ratio
	float colorHeight = DepthWidth * (kinect.getColorSource()->getHeight() / kinect.getColorSource()->getWidth());
	float colorTop = (DepthHeight - colorHeight) / 2.0;

	kinect.getColorSource()->draw(DepthWidth, 0 + colorTop, DepthWidth, colorHeight);
	kinect.getBodySource()->drawProjected(DepthWidth, 0 + colorTop, DepthWidth, colorHeight);

	//kinect.getInfraredSource()->draw(0, DepthHeight, DepthWidth, DepthHeight);

	//kinect.getBodyIndexSource()->draw(DepthWidth, DepthHeight, DepthWidth, DepthHeight);
	//kinect.getBodySource()->drawProjected(DepthWidth, DepthHeight, DepthWidth, DepthHeight, ofxKFW2::ProjectionCoordinates::DepthCamera);

	stringstream ss;
	ss << "fps : " << ofGetFrameRate() << endl;
	ss << "Tracked bodies: " << bodiesTrackedCount;
	if (!haveAllStreams)
	{
		ss << endl << "Not all streams detected!";
	}
	ofDrawBitmapStringHighlight(ss.str(), 20, 20);
}


void KinectTracker::stop()
{
	kinect.close();
}

void KinectTracker::sendImage(const ofImage& image)
{
	
}


ofImage KinectTracker::cropFrame(const ofImage& source, const ofRectangle& sorect)
{
	ofImage image;
	ofImage source_ = source;
	image.cropFrom(source_, sorect.x, sorect.y, sorect.width, sorect.height);
	return image;
}



KinectTracker::~KinectTracker()
{

}