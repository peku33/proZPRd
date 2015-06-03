#include <iostream>
#include "proZPRd/File.hpp"
#include "proZPRd/HttpRequest.hpp"

int main(int ArgC, char ** ArgV)
{
	if(ArgC != 2)
	{
		std::cout << "Usage: " << ArgV[0] << " <HttpRequestDataFileName>" << std::endl;
		return 1;
	}
	auto HttpRequestContent = proZPRd::File::ToString(ArgV[1]);
	
	try
	{
		proZPRd::HTTPRequest R(HttpRequestContent);
		
		std::cout << R.GetURL() << std::endl;
		std::cout << R.GetHost() << std::endl;
		std::cout << R.GetUserAgent() << std::endl;
		std::cout << R.GetRequestedETag() << std::endl;
	}
	catch(const std::exception & E)
	{
		std::cout << E.what() << std::endl;
	}
	return 0;
}