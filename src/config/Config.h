#pragma once
#include "ofMain.h"

namespace bbrother
{
	typedef ofPtr<class Config> ConfigPtr;

	class Config
	{
	public:
		class ApiConfig
		{
		public:
			static const std::vector<std::string> API_FIELD_NAMES;

			ApiConfig();

			const std::string& getValue(const std::string& fieldName);

			void setValue(const std::string& fieldName, const std::string& value);

			~ApiConfig();

		private:
			std::map<std::string, std::string> data;
		};

		Config();

		ofEvent<void> loadCompleteEvent;
		ofEvent<void> loadErrorEvent;
		
		virtual void load();

		virtual ~Config();

	private:
		static const std::string filePath;
		ApiConfig apiData;
	};
}

