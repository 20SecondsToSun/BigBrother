#include "FaceSetHandler.h"
#include "JsonParser.h"
#include "JsonParseFaceSet.h"
#include "JsonParserUserID.h"

using namespace bbrother;

FaceSetHandler::FaceSetHandler() {
	create_url = "https://api-us.faceplusplus.com/facepp/v3/faceset/create";
	display_name = "main_project_face_set";
	faceSetToken = "8defbe2d753677ee696eea726ea03218";

	api_key = "t1y6VUUSmxx8yLUiww5SwiigbR-CWPrr";
	api_secret = "A4dY2MQMKXEJgomNBWNkBANwKGB9ssEe";

	add_url = "https://api-us.faceplusplus.com/facepp/v3/faceset/addface";
	search_url = "https://api-us.faceplusplus.com/facepp/v3/search";

	parser = dynamic_cast<JsonParser<string>*>( new JsonParserFaceSet() );
	parser_results = dynamic_cast<JsonParser<int>*>( new JsonParserUserID() );

	httpUtilsCreate.start();
	httpUtilsAdd.start();
	htttpUtilsSearch.start();
}

void FaceSetHandler::Create() {
	succ = false;
	ofAddListener( httpUtilsCreate.newResponseEvent, this, &FaceSetHandler::newResponseCreate );

	ofxHttpForm form;
	form.action = create_url;

	form.method = HTTPRequestMethod::POST;
	form.addFormField( "api_key", api_key );
	form.addFormField( "api_secret", api_secret );
	form.addFormField( "display_name", display_name );

	httpUtilsCreate.addForm( form );

	std::unique_lock<std::mutex> lock( own_mutex );
	while( !succ ) {
		conditional_variable.wait( lock );
	}
}

void FaceSetHandler::newResponseCreate( ofxHttpResponse & response ) {
	succ = true;
	parser->SetJsonStr( (string)response.responseBody );
	faceSetToken = *parser->Parse();
	assert( faceSetToken != "\0" );
	ofLog( ofLogLevel::OF_LOG_NOTICE, "FaceSet created, token = " + faceSetToken );
	conditional_variable.notify_one();
	std::cout << "Created: " << faceSetToken;
}

void FaceSetHandler::AddFaces(string tokens) {
	succ = false;
	ofAddListener( httpUtilsAdd.newResponseEvent, this, &FaceSetHandler::newResponseAdd );

	ofxHttpForm form;
	form.action = add_url;

	form.method = HTTPRequestMethod::POST;
	form.addFormField( "api_key", api_key );
	form.addFormField( "api_secret", api_secret );
	form.addFormField( "faceset_token", faceSetToken );
	form.addFormField( "face_tokens", tokens );

	httpUtilsAdd.addForm( form );

	std::unique_lock<std::mutex> lock( own_mutex );
	while( !succ ) {
		conditional_variable.wait( lock );
	}
}

int FaceSetHandler::Search(Face* face)
{
	succ = false;
	ofAddListener( htttpUtilsSearch.newResponseEvent, this, &FaceSetHandler::newResponseSearch );

	ofxHttpForm form;
	form.action = search_url;

	form.method = HTTPRequestMethod::POST;
	form.addFormField( "api_key", api_key );
	form.addFormField( "api_secret", api_secret );
	form.addFormField( "face_token", face->getToken() );
	form.addFormField( "faceset_token", faceSetToken );

	htttpUtilsSearch.addForm( form );

	std::unique_lock<std::mutex> lock( own_mutex );
	while( !succ ) {
		conditional_variable.wait( lock );
	}

	if( res != nullptr ) {
		int copy_res = *res;
		delete res;
		return copy_res;
	}
	return -1;
}

void FaceSetHandler::newResponseSearch( ofxHttpResponse& response )
{
	succ = true;
	std::cout << response.responseBody;
	parser_results->SetJsonStr( (string)response.responseBody );
	res = parser_results->Parse();
	conditional_variable.notify_one();
}

void FaceSetHandler::newResponseAdd( ofxHttpResponse& response ) {
	succ = true;
	std:cout << response.responseBody << std::endl;
	conditional_variable.notify_one();
}