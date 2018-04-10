#include "FaceSetHandler.h"
#include "JsonParser.h"
#include "JsonParseFaceSet.h"

using namespace bbrother;

FaceSetHandler::FaceSetHandler() {
	create_url = "https://api-us.faceplusplus.com/facepp/v3/faceset/create";
	display_name = "test_faceset_harry_potter";

	api_key = "t1y6VUUSmxx8yLUiww5SwiigbR-CWPrr";
	api_secret = "A4dY2MQMKXEJgomNBWNkBANwKGB9ssEe";

	add_url = "https://api-us.faceplusplus.com/facepp/v3/faceset/addface";

	parser = dynamic_cast<JsonParser<string>*>( new JsonParserFaceSet() );

	httpUtilsCreate.start();
}

void FaceSetHandler::Create() {
	ofAddListener( httpUtilsCreate.newResponseEvent, this, &FaceSetHandler::newResponseCreate );

	ofxHttpForm form;
	form.action = create_url;

	form.method = HTTPRequestMethod::POST;
	form.addFormField( "api_key", api_key );
	form.addFormField( "api_secret", api_secret );
	form.addFormField( "display_name", display_name );

	httpUtilsCreate.addForm( form );
}

void FaceSetHandler::newResponseCreate( ofxHttpResponse & response ) {
	//std::cout << response.responseBody << std::endl;
	parser->SetJsonStr( (string)response.responseBody );
	faceSetToken = *parser->Parse();
	assert( faceSetToken != "\0" );
	std::cout << faceSetToken;
}

void FaceSetHandler::AddFaces(string tokens) {
	//TODO: concurrency => different httpUtils
	ofAddListener( httpUtilsAdd.newResponseEvent, this, &FaceSetHandler::newResponseAdd );
	httpUtilsAdd.start();

	ofxHttpForm form;
	form.action = add_url;

	form.method = HTTPRequestMethod::POST;
	form.addFormField( "api_key", api_key );
	form.addFormField( "api_secret", api_secret );
	form.addFormField( "faceset_token", "1f91ca19ded7bae7334f7a024882753b" );
	form.addFormField( "face_tokens", tokens );

	httpUtilsAdd.addForm( form );
}

void FaceSetHandler::Search(Face* face)
{
	htttpUtilsSearch.start();
	ofAddListener( htttpUtilsSearch.newResponseEvent, this, &FaceSetHandler::newResponseSearch );

	ofxHttpForm form;
	form.action = "https://api-us.faceplusplus.com/facepp/v3/search";

	form.method = HTTPRequestMethod::POST;
	form.addFormField( "api_key", api_key );
	form.addFormField( "api_secret", api_secret );
	form.addFormField( "face_token", face->getToken() );
	form.addFormField( "faceset_token", "1f91ca19ded7bae7334f7a024882753b" );

	htttpUtilsSearch.addForm( form );
}

void FaceSetHandler::newResponseSearch( ofxHttpResponse& response )
{
	std::cout << response.responseBody;
}

void FaceSetHandler::newResponseAdd( ofxHttpResponse& response ) {
	std:cout << response.responseBody << std::endl;
}