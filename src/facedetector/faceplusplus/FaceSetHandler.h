#pragma once
#include "ofMain.h"
#include "../FaceDetector.h"
#include "FacePlusPlusTypes.h"

#include "../../tools/http/ofxHttpUtils.h"
#include "../../tools/http/ofxHttpTypes.h"
#include "JsonParser.h"

namespace bbrother {
	class FaceSetHandler {
	public:
		FaceSetHandler();
		void Create();
		void AddFaces( string tokens );
		void RemoveFaceSet();
		void Update();
		int Search(Face* face);

	private:
		void newResponseCreate( ofxHttpResponse & response );
		void newResponseAdd( ofxHttpResponse& response );
		void newResponseSearch( ofxHttpResponse& response );


		ofxHttpUtils httpUtilsCreate;
		ofxHttpUtils httpUtilsAdd;
		ofxHttpUtils htttpUtilsSearch;

		string faceSetToken;

		string create_url;
		string add_url;
		string remove_url;
		string update_url;
		
		// TODO: enum
		string display_name;

		//TODO: config
		string api_key;
		string api_secret;
		JsonParser<string>* parser;
		JsonParser<int>* parser_results;


		std::condition_variable conditional_variable;
		std::mutex own_mutex;
		bool succ;
		int* res;
	};
}