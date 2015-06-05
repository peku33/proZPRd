#include <iostream>
#include "proZPRd/HTTPResponse.hpp"
#include "proZPRd/HTTPResponseCode.hpp"
#include "proZPRd/HTTPResponseContent.hpp"
#include "proZPRd/HTTPResponseNotModified.hpp"
#include "proZPRd/HTTPRequest.hpp"
#include "proZPRd/HTTPRequestProcessor.hpp"

/**
* @brief Testy klasy HttpRequestProcessor.
*
*/
int main(int ArgC, char ** ArgV)
{
	proZPRd::HTTPRequestProcessor::HostMapping_t HostMapping;
	proZPRd::HTTPRequestProcessor::ParserMapping_t ParserMapping;

	HostMapping.insert(std::make_pair("127.0.0.1", "."));

	proZPRd::HTTPRequest TestRequest("GET /index.html HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n");
	try
	{
		proZPRd::HTTPRequestProcessor HRP(HostMapping, ParserMapping);
		proZPRd::HTTPResponse::HTTPResponsePtr Response = HRP.Process(TestRequest);

		if((dynamic_cast < proZPRd::HTTPResponseCode* >  (Response.get())) != nullptr )
		{
            std::cout << "Processor returned an object of type HTTPResponseCode" << std::endl;
		}

		if((dynamic_cast < proZPRd::HTTPResponseContent* >  (Response.get())) != nullptr )
		{
            std::cout << "Processor returned an object of type HTTPResponseContent" << std::endl;
		}

		if((dynamic_cast < proZPRd::HTTPResponseNotModified* >  (Response.get())) != nullptr )
		{
            std::cout << "Processor returned an object of type HTTPResponseNotModified" << std::endl;
		}
	}
	catch(const std::exception & E)
	{
		std::cout << E.what() << std::endl;
	}
	return 0;
}
