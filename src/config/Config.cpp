#include "Config.h"
#include "ofxJSON.h"

using namespace bbrother;

Config::Config()
{
	FacePlusPlusData facePlusPlusData = {};
	FamilyBaseData familyBaseData = {};
	KinectData kinectData = {};
	UIData uiData = {};
	ofLog(ofLogLevel::OF_LOG_NOTICE, "Config init");	
}

void Config::setFacePlusPlusData(const FacePlusPlusData& facePlusPlusData)
{
	this->facePlusPlusData = facePlusPlusData;
}

void Config::setFamilyBaseData(const FamilyBaseData& familyBaseData)
{
	this->familyBaseData = familyBaseData;
}

void Config::setKinectData(const KinectData& kinectData)
{
	this->kinectData = kinectData;
}

Config::FacePlusPlusData Config::getFacePlusPlusData() const
{
	return facePlusPlusData;
}

Config::FamilyBaseData Config::getFamilyBaseData() const
{
	return familyBaseData;
}

Config::KinectData Config::getKinectData() const
{
	return kinectData;
}

Config::~Config()
{

}
