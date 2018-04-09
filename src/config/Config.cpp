#include "Config.h"
#include "ofxJSON.h"

using namespace bbrother;

const std::string Config::filePath = "config.json";

Config::Config()
{
	apiData = {};
	ofLog(ofLogLevel::OF_LOG_NOTICE, "Config init");	
}

void Config::load()
{
	ofxJSONElement json;
	bool parsingSuccessful = json.open(Config::filePath);
	if (!parsingSuccessful)
	{
		ofNotifyEvent(loadErrorEvent, this);
		ofLog(ofLogLevel::OF_LOG_ERROR, "Failed to open config");
	}
	else
	{
		apiData.faceProtocol = json["FacePlusPlusApi"]["FaceProtocol"].asString();
		apiData.faceHost = json["FacePlusPlusApi"]["FaceHost"].asString();
		apiData.faceMethod = json["FacePlusPlusApi"]["FaceMethod"].asString();
		apiData.apiKey = json["FacePlusPlusApi"]["APIKey"].asString();
		apiData.apiSecret = json["FacePlusPlusApi"]["APISecret"].asString();
	}

	ofNotifyEvent(loadCompleteEvent, this);
}

const std::string& Config::getApiField(apiField fieldName)
{
	switch (fieldName)
	{
	case FACEPROTOCOL:
		return apiData.faceProtocol;
	case FACEHOST:
		return apiData.faceHost;
	case FACEMETHOD:
		return apiData.faceMethod;
	case APIKEY:
		return apiData.apiKey;
	case APISECRET:
		return apiData.apiSecret;
	default:
		break;
	}
}

void Config::setApiField(apiField fieldName, const std::string& value)
{
	switch (fieldName)
	{
	case FACEPROTOCOL:
		apiData.faceProtocol = value;
		break;
	case FACEHOST:
		apiData.faceHost = value;
		break;
	case FACEMETHOD:
		apiData.faceMethod = value;
		break;
	case APIKEY:
		apiData.apiKey = value;
		break;
	case APISECRET:
		apiData.apiSecret = value;
		break;
	default:
		break;
	}
}

Config::~Config()
{
}

