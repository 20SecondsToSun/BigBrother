#pragma once
#include "ofMain.h"
#include "../../config/Config.h"

namespace bbrother
{
	typedef ofPtr<class FaceDetector> FaceDetectorPtr;

	class FaceDetector 
	{
	public:
		enum class PhotoProcessStatus 
		{
			WaitForPhoto,
			Process,
			Detect,
			NotDetect
		};

		FaceDetector();
		PhotoProcessStatus photoProcessStatus;
		ofEvent<PhotoProcessStatus> photoProcessStatusEvent;
		
		virtual void init(ConfigPtr config) = 0;
		virtual void update() = 0;
		virtual void processImage(const string& path) = 0;
		virtual void processImage(const ofImage& path) = 0;		
		virtual ~FaceDetector();				

		void setPhotoProcessStatus(PhotoProcessStatus status);		
		string getTextPhotoProcessStatus() const;
		string getTextPhotoProcessStatus(PhotoProcessStatus status)const;
	};
}
