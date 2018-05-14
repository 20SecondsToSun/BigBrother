#pragma once
#include "ofMain.h"
#include "Config.h"
#include "ConfigLoader.h"
#include "ConfigParser.h"

namespace bbrother
{
	class ConfigController
	{
	public:
		ConfigController();

		void init(const string& path, ConfigLoader::LoadType type = ConfigLoader::LoadType::LocalFile);

		void onConfigLoadSuccess(string& rawConfig);

		void onConfigLoadError();

		~ConfigController();

		ofEvent<void> configSuccessEvent;
		ofEvent<void> configErrorEvent;

	private:
		std::string configPath;
		ConfigPtr config;
		ConfigLoader configLoader;
		ConfigParser configParser;
	};
}
