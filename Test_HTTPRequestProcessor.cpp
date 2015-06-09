#include <iostream>
#include "proZPRd/File.hpp"
#include "proZPRd/HTTPResponse.hpp"
#include "proZPRd/HTTPResponseCode.hpp"
#include "proZPRd/HTTPResponseContent.hpp"
#include "proZPRd/HTTPResponseNotModified.hpp"
#include "proZPRd/HTTPRequest.hpp"
#include "proZPRd/HTTPRequestProcessor.hpp"
#include "proZPRd/Config.hpp"


/**
* @brief Testy klasy HttpRequestProcessor.
*
*/
int main()
{
	proZPRd::HTTPRequestProcessor::HostMapping_t HostMapping;
	proZPRd::HTTPRequestProcessor::ParserMapping_t ParserMapping;

	HostMapping.insert(std::make_pair("localhost", "./TestData/"));
	HostMapping.insert(std::make_pair("127.0.0.1", "."));

	/**
	*	Tworzymy zapytania, dla ktorych wywolywać będziemy metodę Process.
	*	TestRequestOK - Zapytanie o istniejący plik, nie podajemy ETag - Process powinien zwrócić obiekt
	*					klasy HTTPResponseContent.
	*	TestRequestBadFile - Zapytanie o plik, który nie istnieje - Process powinien zwrócić obiekt klasy
	*					HTTPResponseCode.
	*	TestRequestUnmodified - Zapytanie o istniejący plik, jednak nie różniący się datą modyfikacji od tego
	*					który mamy - Process powinien zwrócić obiekt klasy HTTPResponseNotModified.
	*/
	proZPRd::HTTPRequest TestRequestOK("GET /TestFile.txt HTTP/1.1\r\nHost: localhost\r\n\r\n");
	proZPRd::HTTPRequest TestRequestBadFile("GET /BadFile.txt HTTP/1.1\r\nHost: localhost\r\n\r\n");
	proZPRd::HTTPRequest TestRequestUnmodified("GET /TestFile.txt HTTP/1.1\r\nHost: localhost\r\nIf-None-Match: 1846892-1433451920\r\n\r\n");
	try
	{
		proZPRd::HTTPRequestProcessor HRP(HostMapping, ParserMapping);
		proZPRd::HTTPResponse::HTTPResponsePtr Response = HRP.Process(TestRequestOK);

        std::cout << "TestRequestOK:" << std::endl;

		if((dynamic_cast < proZPRd::HTTPResponseCode* >  (Response.get())) != nullptr )
		{
            std::cout << "Processor returned an object of type HTTPResponseCode" << std::endl;
		}
		else if((dynamic_cast < proZPRd::HTTPResponseContent* >  (Response.get())) != nullptr )
		{
            std::cout << "Processor returned an object of type HTTPResponseContent" << std::endl;
		}
		else if((dynamic_cast < proZPRd::HTTPResponseNotModified* >  (Response.get())) != nullptr )
		{
            std::cout << "Processor returned an object of type HTTPResponseNotModified" << std::endl;
		}

        Response = HRP.Process(TestRequestBadFile);

        std::cout << "TestRequestBadFile:" << std::endl;

		if((dynamic_cast < proZPRd::HTTPResponseCode* >  (Response.get())) != nullptr )
		{
            std::cout << "Processor returned an object of type HTTPResponseCode" << std::endl;
		}
		else if((dynamic_cast < proZPRd::HTTPResponseContent* >  (Response.get())) != nullptr )
		{
            std::cout << "Processor returned an object of type HTTPResponseContent" << std::endl;
		}
		else if((dynamic_cast < proZPRd::HTTPResponseNotModified* >  (Response.get())) != nullptr )
		{
            std::cout << "Processor returned an object of type HTTPResponseNotModified" << std::endl;
		}

        Response = HRP.Process(TestRequestUnmodified);

        std::cout << "TestRequestUnmodified:" << std::endl;

		if((dynamic_cast < proZPRd::HTTPResponseCode* >  (Response.get())) != nullptr )
		{
            std::cout << "Processor returned an object of type HTTPResponseCode" << std::endl;
		}
		else if((dynamic_cast < proZPRd::HTTPResponseContent* >  (Response.get())) != nullptr )
		{
            std::cout << "Processor returned an object of type HTTPResponseContent" << std::endl;
		}
		else if((dynamic_cast < proZPRd::HTTPResponseNotModified* >  (Response.get())) != nullptr )
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
