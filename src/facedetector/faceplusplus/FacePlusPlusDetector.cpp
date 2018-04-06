#include "FacePlusPlusDetector.h"
#include "ofxJSON.h"
#include "json/JsonParserFaceplusPlus.h"

#include "Poco/Base64Encoder.h"
#include "Poco/Buffer.h"

using namespace bbrother;

FacePlusPlusDetector::FacePlusPlusDetector()
{
	ofLog(ofLogLevel::OF_LOG_NOTICE, "Face Plus Plus Detector init");
	ofAddListener(httpService.ServerResponseEvent, this, &FacePlusPlusDetector::onServerResponse);
}

void FacePlusPlusDetector::init(ConfigPtr config)
{
	string FACE_PROTOCOL = "https";
	string FACE_HOST = "api-us.faceplusplus.com";
	string FACE_METHOD = "facepp/v3/detect";
	
	FACE_URL = FACE_PROTOCOL + "://" + FACE_HOST + "/" + FACE_METHOD;
	API_KEY = "t1y6VUUSmxx8yLUiww5SwiigbR-CWPrr";
	API_SECRET = "A4dY2MQMKXEJgomNBWNkBANwKGB9ssEe";

	setPhotoProcessStatus(PhotoProcessStatus::WaitForPhoto);
}

void FacePlusPlusDetector::processImage(const string& path) 
{
	setPhotoProcessStatus(PhotoProcessStatus::Process);

	vector<HttpService::RequestParam> requestParams;
	requestParams.push_back(HttpService::RequestParam("api_key", API_KEY));
	requestParams.push_back(HttpService::RequestParam("api_secret", API_SECRET));
	requestParams.push_back(HttpService::RequestParam("return_attributes", "gender,age,ethnicity,beauty"));

	HttpService::RequestParam fileParam("image_file", path);

	vector<HttpService::HeaderParam> headerParams;
	httpService.makeRequest(FACE_URL, HTTPRequestMethod::POST, requestParams, headerParams, fileParam);
}

void FacePlusPlusDetector::processImage(const ofImage& personImage)
{
	setPhotoProcessStatus(PhotoProcessStatus::Process);

	vector<HttpService::RequestParam> requestParams;
	requestParams.push_back(HttpService::RequestParam("api_key", API_KEY));
	requestParams.push_back(HttpService::RequestParam("api_secret", API_SECRET));
	requestParams.push_back(HttpService::RequestParam("return_attributes", "gender,age,ethnicity,beauty"));

	
	ofBuffer buffer;
	ofSaveImage(const_cast<ofImage&>(personImage).getPixelsRef(), buffer, OF_IMAGE_FORMAT_JPEG, OF_IMAGE_QUALITY_BEST);
	stringstream ss;
	Poco::Base64Encoder b64enc(ss);
	b64enc << buffer;

	requestParams.push_back(HttpService::RequestParam("image_base64", ss.str()));
	
	vector<HttpService::HeaderParam> headerParams;
	httpService.makeRequest(FACE_URL, HTTPRequestMethod::POST, requestParams, headerParams);
}

void FacePlusPlusDetector::update()
{
	httpService.update();
}

void FacePlusPlusDetector::onServerResponse(const string& response)
{
	JsonParserFaceplusPlus parser(response);
	bool success = parser.parse();

	if (success)
	{
		FacePtr face = parser.getFace();
		setPhotoProcessStatus(PhotoProcessStatus::Detect);
		face->print();
	}
	else
	{
		setPhotoProcessStatus(PhotoProcessStatus::NotDetect);
	}
}

FacePlusPlusDetector::~FacePlusPlusDetector()
{

}