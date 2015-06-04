#include "proZPRd/Logger.hpp"
#include "proZPRd/HTTPRequestProcessor.hpp"
#include "proZPRd/Server.hpp"

int main()
{
	proZPRd::Logger::Ok("proZPRd starting...");
	
	proZPRd::HTTPRequestProcessor::HostMapping_t Mapping;
	Mapping["d.peku33.net:8080"] = "/home/peku33/public_html";
	Mapping["127.0.0.1:8080"] = ".";
	
	proZPRd::HTTPRequestProcessor HRP(Mapping);
	
	{ proZPRd::Server MainServer("0.0.0.0", 8080, 4, HRP); MainServer.Run(); }
	
	
	proZPRd::Logger::Info("Press ANY key to exit...");
	getc(stdin);
	return 0;
}