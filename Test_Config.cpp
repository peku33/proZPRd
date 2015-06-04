#include <iostream>
#include "proZPRd/Config.hpp"
#include "proZPRd/Logger.hpp"

int main(int ArgC, char ** ArgV)
{
	std::cout << "Program testujacy odczyt podanego configu" << std::endl;
	if(ArgC != 2)
	{
		std::cout << "Uzycie: " << ArgV[0] << " <Nazwa Configu>" << std::endl;
		return 1;
	}
	try
	{
		proZPRd::Config C(ArgV[1]);
		std::cout << "ThreadsNum: " << C.GetThreadsNum() << std::endl;
		std::cout << "BindAddress: " << C.GetBindAddress() << std::endl;
		std::cout << "BindPort: " << C.GetBindPort() << std::endl;
		for(auto & Host : C.GetHostMapping())
			std::cout << "VHost: `" << Host.first << "` -> `" << Host.second << "`" << std::endl;
		for(auto & Parser : C.GetParserMapping())
			std::cout << "RegEx: `" << Parser.first << "` -> `" << Parser.second << "`" << std::endl;
	}
	catch(const std::exception & E)
	{
		proZPRd::Logger::Error(E.what());
	}
	return 0;
}