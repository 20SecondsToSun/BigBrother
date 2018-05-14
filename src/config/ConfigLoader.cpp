#include "ConfigLoader.h"

using namespace bbrother;

ConfigLoader::ConfigLoader()
{

}

void ConfigLoader::load(const string& param, LoadType type)
{
	if (type == LoadType::LocalFile)
	{
		if (param.length() > 0)
		{
			configPath = param;
			configBuffer = ofBufferFromFile(configPath);
			string configText = configBuffer.getText();
			loadSuccessEvent.notify(this, configText);
		}
		else
		{
			ofLog(ofLogLevel::OF_LOG_ERROR, "Failed to open config");
			configErrorEvent.notify(this);
		}
	}
}

ConfigLoader::~ConfigLoader()
{

}
