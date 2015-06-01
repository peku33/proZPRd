#pragma once

#include <string>
#include <set>
namespace proZPRd
{
	/**
		Klasa parsująca plik konfiguracyjny ini. 
	*/
	class IniParser
	{		
		private:
			std::string Dir;
			std::string Errorlog;
			int Port;
			int Threads;
			std::set<std::string> AdditionalParsers;
		
		public:
			IniParser(const std::string & Input);
			std::string GetDir() {return Dir;};
			std::string GetErrorlog() {return  Errorlog;};
			int GetPort() {return Port;};
			int GetThreads() {return Threads;};
			std::set<std::string> GetAdditionalParsers() {return AdditionalParsers;};
	};
}
