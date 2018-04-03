#include "Config.h"
#include "ofxJSON.h"

using namespace bbrother;

const std::string Config::filePath = "config.json";
const std::vector<std::string> Config::ApiConfig::API_FIELD_NAMES = {
	"FaceProtocol","FaceHost", "FaceMethod", "APIKey", "APISecret" };

Config::ApiConfig::ApiConfig()
{
	for (const std::string& fieldName : API_FIELD_NAMES)
	{
		data.insert(std::pair<std::string, std::string>(fieldName, ""));
	}
}

const std::string& Config::ApiConfig::getValue(const std::string& fieldName)
{
	return data.at(fieldName);
}

void Config::ApiConfig::setValue(const std::string& fieldName, const std::string& value)
{
	data.at(fieldName) = value;
}

Config::ApiConfig::~ApiConfig()
{

}

Config::Config()
{
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

	for (const std::string& fieldName : Config::ApiConfig::API_FIELD_NAMES)
	{
		std::string& value = json["FacePlusPlusApi"][fieldName].asString();
		apiData.setValue(fieldName, value);
	}
	
	ofNotifyEvent(loadCompleteEvent, this);
}

Config::~Config()
{

}

