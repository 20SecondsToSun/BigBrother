#include "ConfigParser.h"

using namespace bbrother;

ConfigParser::ConfigParser()
{

}

void ConfigParser::parse(ConfigPtr config, const string& configString)
{
	bool parsingSuccessful = configResult.parse(configString);

	if (parsingSuccessful)
	{
		Config::FacePlusPlusData facePlusPlusData;
		facePlusPlusData.faceProtocol = configResult["faceProtocol"].asString();
		facePlusPlusData.faceHost = configResult["faceHost"].asString();
		facePlusPlusData.faceDetectMethod = configResult["faceDetectMethod"].asString();
		facePlusPlusData.faceSearchMethod = configResult["faceSearchMethod"].asString();
		facePlusPlusData.APIKey = configResult["APIKey"].asString();
		facePlusPlusData.APISecret = configResult["APISecret"].asString();
		config->setFacePlusPlusData(facePlusPlusData);

		Config::FamilyBaseData familyBaseData;
		familyBaseData.familyProtocol = configResult["familyProtocol"].asString();
		familyBaseData.familyHost = configResult["familyHost"].asString();
		familyBaseData.grantType = configResult["grantType"].asString();
		familyBaseData.clientId = configResult["clientId"].asInt();
		familyBaseData.clientSecret = configResult["clientSecret"].asString();
		familyBaseData.username = configResult["username"].asString();
		familyBaseData.password = configResult["password"].asString();
		config->setFamilyBaseData(familyBaseData);

		Config::KinectData kinectData;
		kinectData.depthWidth = configResult["depthWidth"].asInt();
		kinectData.depthHeight = configResult["depthHeight"].asInt();
		kinectData.colorWidth = configResult["colorWidth"].asInt();
		kinectData.depthWidth = configResult["colorHeight"].asInt();
		config->setKinectData(kinectData);

		parseConfigSuccessEvent.notify(this);
	}
	else
	{
		parseConfigErrorEvent.notify(this);
	}
}

ConfigParser::~ConfigParser()
{

}