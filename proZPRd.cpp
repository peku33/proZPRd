#include "proZPRd/Logger.hpp"
#include "proZPRd/Config.hpp"
#include "proZPRd/HTTPRequestProcessor.hpp"
#include "proZPRd/Server.hpp"
#include "proZPRd/Tools/Exception.hpp"

#include <thread>
#include <iostream>

int main(int ArgC, char ** ArgV)
{
	if(ArgC != 2)
	{
		std::cout << "Usage:" << ArgV[0] << " <ConfigFile>" << std::endl;
		return 1;
	}
	proZPRd::Logger::Info("proZPRd init...");
	
	try
	{
		proZPRd::Logger::Info("Reading config");
		proZPRd::Config MainConfig(ArgV[1]);
		
		unsigned int SuggestedThreadsNum = std::thread::hardware_concurrency();
		unsigned int MaxThreadsNum = SuggestedThreadsNum * 8;
		unsigned int ThreadsNum = MainConfig.GetThreadsNum();
		if(ThreadsNum == 0)
			ThreadsNum = SuggestedThreadsNum;
		else if(ThreadsNum > MaxThreadsNum)
			throw proZPRd::Tools::Exception(EXCEPTION_PARAMS, "ThreadsNum is too high for this machine. Suggested maximum: " + std::to_string(MaxThreadsNum));

		proZPRd::HTTPRequestProcessor HRP(MainConfig.GetHostMapping(), MainConfig.GetParserMapping());

		{ proZPRd::Logger::Ok("Starting server"); proZPRd::Server MainServer(MainConfig.GetBindAddress(), MainConfig.GetBindPort(), ThreadsNum, HRP); MainServer.Run(); }
	
	}
	catch(const std::exception & E)
	{
		proZPRd::Logger::Error(E.what());
	}
	
	proZPRd::Logger::Info("Press ANY key to exit...");
	getc(stdin);
	return 0;
}