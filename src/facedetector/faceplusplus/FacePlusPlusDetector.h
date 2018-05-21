#pragma once
#include "ofMain.h"
#include "../FaceDetector.h"
#include "FacePlusPlusTypes.h"

#include "../../tools/http/ofxHttpUtils.h"
#include "../../tools/http/ofxHttpTypes.h"
#include "JsonParser.h"
#include <condition_variable>
#include <mutex>

namespace bbrother
{
	typedef ofPtr<class FacePlusPlusDetector> FacePlusPlusDetectorPtr;

	class FacePlusPlusDetector : public FaceDetector
	{
	public:
		FacePlusPlusDetector();
		virtual void init( ConfigPtr config ) override;
		virtual Face* ProcessImage( string path ) override;
		virtual void AddUserId( int id, string token ) override;
		virtual ~FacePlusPlusDetector() override;

	private:
		ofxHttpUtils httpUtils;
		ofxHttpUtils httpUtilsUserID;

		void makeRequest(const string& FACE_URL, const string& API_KEY, const string& API_SECRET, const string& filePath);
		void newResponse( ofxHttpResponse & response );

		void ResponseUserId( ofxHttpResponse & response );

		string FACE_URL;
		string API_KEY;
		string API_SECRET;
		string path;

		Face* res;
		bool succ;
		JsonParser<Face>* parser;

		std::condition_variable conditional_variable;
		std::mutex own_mutex;
	};
}

