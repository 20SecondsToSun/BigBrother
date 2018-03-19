#pragma once
#include "ofMain.h"
#include "../FaceDetector.h"
#include "FacePlusPlusTypes.h"

#include "../../tools/http/ofxHttpUtils.h"
#include "../../tools/http/ofxHttpTypes.h"

namespace bbrother
{
	typedef ofPtr<class FacePlusPlusDetector> FacePlusPlusDetectorPtr;

	class FacePlusPlusDetector : public FaceDetector
	{
	public:
		FacePlusPlusDetector();
		virtual void init( ConfigPtr config ) override;
		virtual ~FacePlusPlusDetector();

		void ProcessImage(string path) override;

	private:
		Face face;
		ofxHttpUtils httpUtils;

		void makeRequest(const string& FACE_URL, const string& API_KEY, const string& API_SECRET, const string& filePath);
		void newResponse(ofxHttpResponse & response);	

		string FACE_URL;
		string API_KEY;
		string API_SECRET;
		string path;
	};
}

