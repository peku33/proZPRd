#pragma once

#include <string>
#include "HTTPRequestProcessor.hpp"

namespace proZPRd
{
	/**
		Klasa reprezentująca plik konfiguracyjny
	*/
	class Config
	{
		public:
			Config(const std::string & FileName);
		
		private:
			const std::string FileName;
		
		private:
			unsigned int ThreadsNum;
			std::string BindAddress;
			unsigned int BindPort;
			HTTPRequestProcessor::HostMapping_t HostMapping;
			HTTPRequestProcessor::ParserMapping_t ParserMapping;
		
		public:
			unsigned int GetThreadsNum() const;
			std::string GetBindAddress() const;
			unsigned int GetBindPort() const;
			HTTPRequestProcessor::HostMapping_t GetHostMapping() const;
			HTTPRequestProcessor::ParserMapping_t GetParserMapping() const;
	};
}