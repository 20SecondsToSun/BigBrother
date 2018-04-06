#pragma once
#include "ofMain.h"
#include "../abstract/FaceDetector.h"
#include "FacePlusPlusTypes.h"

#include "../../tools/http/HttpService.h"
#include "../../tools/http/ofxHttpTypes.h"

namespace bbrother
{
	typedef ofPtr<class FacePlusPlusDetector> FacePlusPlusDetectorPtr;

	class FacePlusPlusDetector : public FaceDetector
	{
	public:
		FacePlusPlusDetector();
		virtual ~FacePlusPlusDetector();

		virtual void init(ConfigPtr config) override;
		virtual void update() override;	
		virtual void processImage(const string& path) override;
		virtual void processImage(const ofImage& path) override;

	private:
		Face face;
		HttpService httpService;

		void onServerResponse(const string& response);
		
		string FACE_URL;
		string API_KEY;
		string API_SECRET;
		string path;
	};
}

