#include "FacePlusPlusDetector.h"
#include "ofxJSON.h"
#include "JsonParserFace.h"
#include "JsonParser.h"
#include "FaceSetHandler.h"
#include <utility>
#include "ofThread.h"

using namespace bbrother;

FacePlusPlusDetector::FacePlusPlusDetector()
{
	ofLog(ofLogLevel::OF_LOG_NOTICE, "Face Plus Plus Detector init");	
}

void FacePlusPlusDetector::init( ConfigPtr config )
{
	string FACE_PROTOCOL = "https";
	string FACE_HOST = "api-us.faceplusplus.com";
	string FACE_METHOD = "facepp/v3/detect";
	
	FACE_URL = FACE_PROTOCOL + "://" + FACE_HOST + "/" + FACE_METHOD;
	API_KEY = "t1y6VUUSmxx8yLUiww5SwiigbR-CWPrr";
	API_SECRET = "A4dY2MQMKXEJgomNBWNkBANwKGB9ssEe";

	test = WaitForPhoto;
	ofNotifyEvent( status_event, test );

	parser = dynamic_cast<JsonParser<Face>*>(new JsonParserFace());

	httpUtils.start();
	httpUtilsUserID.start();
}

Face* FacePlusPlusDetector::ProcessImage(string path_) {
	path = path_;
	res = nullptr;
	makeRequest(FACE_URL, API_KEY, API_SECRET, path );
	return res;
}

void FacePlusPlusDetector::AddUserId( int id, string token ) {
	succ = false;

	ofAddListener( httpUtilsUserID.newResponseEvent, this, &FacePlusPlusDetector::ResponseUserId );

	ofxHttpForm form;
	form.action = "https://api-us.faceplusplus.com/facepp/v3/face/setuserid";
	form.method = HTTPRequestMethod::POST;
	form.addFormField( "api_key", API_KEY );
	form.addFormField( "api_secret", API_SECRET );
	form.addFormField( "face_token", token );
	form.addFormField( "user_id",  std::to_string(id));
	httpUtilsUserID.addForm( form );

	std::unique_lock<std::mutex> lock( own_mutex );
	while( res == nullptr ) {
		conditional_variable.wait( lock );
	}
}

void FacePlusPlusDetector::ResponseUserId( ofxHttpResponse & response ) {
	succ = true;
	std::cout << response.responseBody << std::endl;
	conditional_variable.notify_one();
}

void FacePlusPlusDetector::makeRequest(const string& FACE_URL, const string& API_KEY, const string& API_SECRET, const string& filePath)
{
	//httpUtils.start();
	test = Process;
	ofNotifyEvent( status_event, test );

	ofAddListener(httpUtils.newResponseEvent, this, &FacePlusPlusDetector::newResponse);

	ofxHttpForm form;
	form.action = FACE_URL;
	//cout << "FACE_URL: " << FACE_URL << endl;
	form.method = HTTPRequestMethod::POST;
	form.addFormField("api_key", API_KEY);
	form.addFormField("api_secret", API_SECRET);
	form.addFile("image_file", filePath);
	form.addFormField( "return_attributes", "gender,age,ethnicity,beauty" );
	httpUtils.addForm(form);

	std::unique_lock<std::mutex> lock( own_mutex );
	while( res == nullptr ) {
		conditional_variable.wait(lock);
	}
	//httpUtils.stop();
}


void FacePlusPlusDetector::newResponse( ofxHttpResponse & response)
{
	string response_body = response.responseBody;
	std::cout << "newResponse" << std::endl;
	parser->SetJsonStr(response_body );
	res = parser->Parse();
	//FaceSetHandler* faceSet = new FaceSetHandler();
	//faceSet->Create();

	if( res == nullptr ) {
		test = NotDetect;
		ofNotifyEvent( status_event, test );
		std::cout << "ERROR" << std::endl;
	} else {
		test = Detect;
		ofNotifyEvent( status_event, test );
		//faceSet->AddFaces( res->getToken() );
	}
	conditional_variable.notify_one();
}

FacePlusPlusDetector::~FacePlusPlusDetector()
{
	delete parser;
	//httpUtils.stop();
}
