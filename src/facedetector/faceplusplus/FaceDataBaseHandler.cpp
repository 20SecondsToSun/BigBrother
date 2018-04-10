#include "FaceDataBaseHandler.h"
#include "JsonParserDB.h"

using namespace bbrother;

FaceDataBaseHandler::FaceDataBaseHandler() {
	//TODO: убрать, все должно быть в конфиг парсере
	authorize_url = "http://bbrother.familyagency.ru/oauth/token";
	create_url = "http://bbrother.familyagency.ru/api/users/";
	get_all_url = "http://bbrother.familyagency.ru/api/users/";
	client_id = "9";
	client_secret = "aPafZ4En98b5SIpCYsa9ehAOpfk0AWzQTylAyLR6";
	grant_type = "password";
	most_secret_pwd = "kittycat123";
	email = "litv.daria@gmail.com";
	parser = dynamic_cast<JsonParser<DataBaseParams>*>( new JsonParserDB() );
	data_base_params = nullptr;
	httpUtils.start();
	authorize();
}

FaceDataBaseHandler::~FaceDataBaseHandler() {
	delete parser;
	delete data_base_params;
}

void FaceDataBaseHandler::CreateUser( string name, string token ) {
	ofAddListener( httpUtils.newResponseEvent, this, &FaceDataBaseHandler::newResponseCreate );

	ofxHttpForm form;
	form.action = create_url;
	cout << "FACE_URL: " << create_url << endl;

	form.method = HTTPRequestMethod::POST;
	form.addHeaderField( "Content-Type", "application/json" );
	form.addHeaderField( "Authorization", "Bearer " + data_base_params->access_token);
	form.addFormField( "name", name );
	form.addFormField( "master_token", token );

	httpUtils.addForm( form );
}

void FaceDataBaseHandler::newResponseCreate( ofxHttpResponse& response )
{
	std::cout << response.responseBody << std::endl;
}

void FaceDataBaseHandler::GetAll() {
	ofAddListener( httpUtils.newResponseEvent, this, &FaceDataBaseHandler::newResponseGetAll);
	succ = false;
	ofxHttpForm form;
	form.action = get_all_url;
	cout << "FACE_URL: " << get_all_url << endl;

	form.method = HTTPRequestMethod::GET;
	form.addHeaderField( "Content-Type", "application/json" );
	form.addHeaderField( "Authorization", "Bearer " + data_base_params->access_token );

	httpUtils.addForm( form );

	std::unique_lock<std::mutex> lock( own_mutex );
	while( !succ ) {
		conditional_variable.wait( lock );
	}
}

void FaceDataBaseHandler::newResponseGetAll( ofxHttpResponse& response )
{
	succ = true;
	std::cout << response.responseBody << std::endl;
	conditional_variable.notify_one();
}

void FaceDataBaseHandler::RemoveFace() {

}

void FaceDataBaseHandler::Update() {

}

void FaceDataBaseHandler::authorize() {
	ofAddListener( httpUtils.newResponseEvent, this, &FaceDataBaseHandler::newResponseAuthorize );

	ofxHttpForm form;
	form.action = authorize_url;
	cout << "FACE_URL: " << authorize_url << endl;

	form.method = HTTPRequestMethod::POST;
	form.addHeaderField( "Content-Type", "application/json" );
	form.addFormField( "grant_type", grant_type );
	form.addFormField( "client_id", client_id );
	form.addFormField( "client_secret",  client_secret);
	form.addFormField( "username", email );
	form.addFormField( "password", most_secret_pwd );

	httpUtils.addForm( form );

	std::unique_lock<std::mutex> lock(own_mutex);
	while( data_base_params == nullptr ) {
		conditional_variable.wait(lock);
	}
}

void FaceDataBaseHandler::newResponseAuthorize( ofxHttpResponse & response ) {
	parser->SetJsonStr( (string)response.responseBody );
	data_base_params = parser->Parse();
	conditional_variable.notify_one();
}