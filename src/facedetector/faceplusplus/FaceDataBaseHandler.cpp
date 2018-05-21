#include "FaceDataBaseHandler.h"
#include "JsonParserDB.h"
#include "JsonParserUserID.h"

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
	parser_id = dynamic_cast<JsonParser<int>*>( new JsonParserUserID() );
	data_base_params = nullptr;
	httpUtils_authorize.start();
	authorize();
	httpUtils_authorize.stop();
	httpUtils_get_all.start();
	httpUtils_create.start();
	httpUtils_delete.start();
	httpUtils_get_one.start();
	httpUtils_create_token.start();
}

FaceDataBaseHandler::~FaceDataBaseHandler() {
	delete parser;
	delete data_base_params;
	//httpUtils.stop();
}

int FaceDataBaseHandler::CreateUser( string name, string token ) {
	//httpUtils_create.start();
	res = false;
	ofAddListener( httpUtils_create.newResponseEvent, this, &FaceDataBaseHandler::newResponseCreate );

	ofxHttpForm form;
	form.action = create_url;
	cout << "FACE_URL: " << create_url << endl;

	form.method = HTTPRequestMethod::POST;
	form.addHeaderField( "Content-Type", "application/json" );
	form.addHeaderField( "Authorization", "Bearer " + data_base_params->access_token);
	form.addFormField( "name", name );
	form.addFormField( "master_token", token );

	httpUtils_create.addForm( form );
	
	std::unique_lock<std::mutex> lock( own_mutex );
	while( !res ) {
		conditional_variable.wait( lock );
	}
	return user_id;
	//httpUtils_create.stop();
}

void FaceDataBaseHandler::newResponseCreate( ofxHttpResponse& response )
{
	std::cout << response.responseBody << std::endl;
	res = true;
	parser_id->SetJsonStr( (string)response.responseBody );
	int* id = parser_id->Parse();
	user_id = *id;
	delete id;
	conditional_variable.notify_one();
}

void FaceDataBaseHandler::CreateToken( int id, string token ) {
	res = false;
	ofAddListener( httpUtils_create_token.newResponseEvent, this, &FaceDataBaseHandler::newResponseCreateToken );

	ofxHttpForm form;
	form.action = "http://bbrother.familyagency.ru/api/faceTokens/";
	cout << "FACE_URL: " << form.action << endl;

	form.method = HTTPRequestMethod::POST;
	form.addHeaderField( "Content-Type", "application/json" );
	form.addHeaderField( "Authorization", "Bearer " + data_base_params->access_token );
	form.addFormField( "user_id", std::to_string( id ) );
	form.addFormField( "face_token", token );

	httpUtils_create_token.addForm( form );

	std::unique_lock<std::mutex> lock( own_mutex );
	while( !res ) {
		conditional_variable.wait( lock );
	}
}

void FaceDataBaseHandler::newResponseCreateToken( ofxHttpResponse& response )
{
	std::cout << response.responseBody << std::endl;
	res = true;
	conditional_variable.notify_one();
}


void FaceDataBaseHandler::GetAll() {
	//httpUtils_get_all.start();
	ofAddListener( httpUtils_get_all.newResponseEvent, this, &FaceDataBaseHandler::newResponseGetAll);
	succ = false;
	ofxHttpForm form;
	form.action = get_all_url;
	cout << "FACE_URL: " << get_all_url << endl;

	form.method = HTTPRequestMethod::GET;
	form.addHeaderField( "Content-Type", "application/json" );
	form.addHeaderField( "Authorization", "Bearer " + data_base_params->access_token );

	httpUtils_get_all.addForm( form );

	std::unique_lock<std::mutex> lock( own_mutex );
	while( !succ ) {
		conditional_variable.wait( lock );
	}
	//httpUtils_get_all.waitForThread( true );
}

void FaceDataBaseHandler::newResponseGetAll( ofxHttpResponse& response )
{
	succ = true;
	std::cout << response.responseBody << std::endl;
	conditional_variable.notify_one();
}

void FaceDataBaseHandler::GetOne(int id) {
	//httpUtils_get_one.start();
	ofAddListener( httpUtils_get_one.newResponseEvent, this, &FaceDataBaseHandler::newResponseGetOne );
	succ = false;
	ofxHttpForm form;
	form.action = get_all_url + std::to_string(id);
	cout << "FACE_URL: " << form.action << endl;

	form.method = HTTPRequestMethod::GET;
	form.addHeaderField( "Content-Type", "application/json" );
	form.addHeaderField( "Authorization", "Bearer " + data_base_params->access_token );

	httpUtils_get_one.addForm( form );

	std::unique_lock<std::mutex> lock( own_mutex );
	while( !succ ) {
		conditional_variable.wait( lock );
	}
	//httpUtils_get_one.stop();
}

void FaceDataBaseHandler::newResponseGetOne( ofxHttpResponse& response )
{
	succ = true;
	std::cout << response.responseBody << std::endl;
	conditional_variable.notify_one();
}

void FaceDataBaseHandler::RemoveFace(int id) {
	//httpUtils_delete.start();
	succ = false;
	ofAddListener( httpUtils_delete.newResponseEvent, this, &FaceDataBaseHandler::newResponseRemove );

	ofxHttpForm form;
	form.action = get_all_url + std::to_string(id);
	cout << "FACE_URL: " << create_url << endl;

	form.method = HTTPRequestMethod::_DELETE;
	form.addHeaderField( "Content-Type", "application/json" );
	form.addHeaderField( "Authorization", "Bearer " + data_base_params->access_token );

	httpUtils_delete.addForm( form );

	std::unique_lock<std::mutex> lock( own_mutex );
	while( !succ ) {
		conditional_variable.wait( lock );
	}
	//httpUtils_delete.stop();
}

void FaceDataBaseHandler::newResponseRemove( ofxHttpResponse& response )
{
	succ = true;
	std::cout << response.responseBody << std::endl;
	conditional_variable.notify_one();
}

void FaceDataBaseHandler::Update() {

}

void FaceDataBaseHandler::authorize() {
	ofAddListener( httpUtils_authorize.newResponseEvent, this, &FaceDataBaseHandler::newResponseAuthorize );

	ofxHttpForm form;
	form.action = authorize_url;
	//cout << "FACE_URL: " << authorize_url << endl;

	form.method = HTTPRequestMethod::POST;
	form.addHeaderField( "Content-Type", "application/json" );
	form.addFormField( "grant_type", grant_type );
	form.addFormField( "client_id", client_id );
	form.addFormField( "client_secret",  client_secret);
	form.addFormField( "username", email );
	form.addFormField( "password", most_secret_pwd );

	httpUtils_authorize.addForm( form );

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