#pragma once
#include "ofMain.h"
#include "../FaceDetector.h"
#include "FacePlusPlusTypes.h"

#include "../../tools/http/ofxHttpUtils.h"
#include "../../tools/http/ofxHttpTypes.h"
#include "JsonParser.h"
#include <condition_variable>
#include <mutex>


namespace bbrother {
	struct DataBaseParams {
		string expires_in;
		string access_token;
		string refresh_token;
	};

	class FaceDataBaseHandler {
	public:
		FaceDataBaseHandler();
		void CreateUser(string name, string token);
		string GetTokenById();
		void GetAll();
		void RemoveFace();
		void Update();
		~FaceDataBaseHandler();
	private:
		void authorize();
		void newResponseAuthorize( ofxHttpResponse & response );
		void newResponseCreate( ofxHttpResponse& response );
		void newResponseGetAll( ofxHttpResponse& response );


		ofxHttpUtils httpUtils;
		string authorize_url;
		string create_url;
		string get_all_url;
		string client_id;
		string client_secret;
		string grant_type;
		string most_secret_pwd;
		string email;

		JsonParser<DataBaseParams>* parser;

		DataBaseParams* data_base_params;

		std::condition_variable conditional_variable;
		std::mutex own_mutex;
		bool succ;
	};
}