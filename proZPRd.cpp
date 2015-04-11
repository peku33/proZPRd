#include "proZPRd/Logger.hpp"

int main()
{
	proZPRd::Logger::Ok("proZPRd starting...");
	
	
	proZPRd::Logger::Info("Press ANY key to exit...");
	getc(stdin);
	return 0;
}