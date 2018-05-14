#include "ConfigController.h"

using namespace bbrother;

ConfigController::ConfigController()
{
	config = ConfigPtr(new Config());
}

void ConfigController::init(const string& path, ConfigLoader::LoadType type)
{
	configPath = path;
	ofAddListener(configLoader.loadSuccessEvent, this, &ConfigController::onConfigLoadSuccess);
	ofAddListener(configLoader.configErrorEvent, this, &ConfigController::onConfigLoadError);
	configLoader.load(configPath);
}

void ConfigController::onConfigLoadSuccess(string& rawConfig)
{
	configParser.parse(config, rawConfig);
}

void ConfigController::onConfigLoadError()
{
	configErrorEvent.notify(this);
}

ConfigController::~ConfigController()
{

}
