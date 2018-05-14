#pragma once
#include "ofMain.h"

namespace bbrother
{
	class ConfigLoader
	{
	public:
		enum LoadType
		{
			None,
			LocalFile,
			Url,
			Resource
		};

		ConfigLoader();

		ofEvent<string> loadSuccessEvent;
		ofEvent<void> configErrorEvent;

		void load(const string& param, LoadType type = LoadType::LocalFile);

		~ConfigLoader();

	private:
		string configPath;
		ofBuffer configBuffer;
	};
}
