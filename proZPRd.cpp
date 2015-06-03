#include "proZPRd/Logger.hpp"
#include "proZPRd/Server.hpp"

int main()
{
	proZPRd::Logger::Ok("proZPRd starting...");
	
	proZPRd::Server MainServer("0.0.0.0", 8080, 4);
	MainServer.Run();
	
	
	proZPRd::Logger::Info("Press ANY key to exit...");
	getc(stdin);
	return 0;
}