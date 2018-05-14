#pragma once
#include "ofMain.h"
#include "Config.h"
#include "ofxJSON.h"

namespace bbrother
{
	class ConfigParser
	{
	public:
		ConfigParser();

		ofEvent<void> parseConfigSuccessEvent;
		ofEvent<void> parseConfigErrorEvent;

		void parse(ConfigPtr config, const string& configString);

		~ConfigParser();

	private:
		ofxJSONElement configResult;
	};
}
