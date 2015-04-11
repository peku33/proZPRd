#include "proZPRd/Logger.hpp"

int main()
{
	proZPRd::Logger::Ok("proZPRd starting...");
	
	
	proZPRd::Logger::Ok("Press ANY key to exit...");
	getc(stdin);
	return 0;
}