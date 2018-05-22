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
		int CreateUser(string name, string token);
		string GetTokenById();
		void GetAll();
		void GetOne( int id );
		void CreateToken( int id, string token );
		void RemoveFace(int id);
		void Update();
		~FaceDataBaseHandler();
	private:
		void authorize();
		void newResponseAuthorize( ofxHttpResponse & response );
		void newResponseCreate( ofxHttpResponse& response );
		void newResponseGetAll( ofxHttpResponse& response );
		void newResponseGetOne( ofxHttpResponse& response );
		void newResponseRemove( ofxHttpResponse& response );
		void newResponseCreateToken( ofxHttpResponse& response );


		ofxHttpUtils httpUtils_authorize;
		
		ofxHttpUtils httpUtils_get_all;
		ofxHttpUtils httpUtils_get_one;

		ofxHttpUtils httpUtils_create;
		ofxHttpUtils httpUtils_change;
		ofxHttpUtils httpUtils_delete;
		ofxHttpUtils httpUtils_create_token;

		string authorize_url;
		string create_url;
		string get_all_url;
		string client_id;
		string client_secret;
		string grant_type;
		string most_secret_pwd;
		string email;

		JsonParser<DataBaseParams>* parser;
		JsonParser<int>* parser_id;

		DataBaseParams* data_base_params;

		std::condition_variable conditional_variable;
		std::mutex own_mutex;
		bool success;
		int user_id;
	};
}