#include "HTTPRequest.hpp"

#include "Strings.hpp"
#include "Tools/Exception.hpp"
#include <stdexcept>

proZPRd::HTTPRequest::HTTPRequest(const std::string & Request)
{
	// Linie z kolejnymi danymi
	auto Lines = Strings::SplitString(Request, "\r\n");
	
	/*
		Tu następuje podział pierwszej linii na części
		
		Pierwsza linia:
			[0] => HttpMethod
			[1] => Url
			[2] => HTTPVersion
	*/
	auto RequestParts = Strings::SplitString(Lines[0], " ");
	if(RequestParts.size() != 3)
		throw Tools::Exception(EXCEPTION_PARAMS, "Illformed HTTP Request first line");
	
	if(RequestParts[0] != "GET")
		throw Tools::Exception(EXCEPTION_PARAMS, "Unkown HTTPMethod `" + RequestParts[0] + "`");
		
	if(RequestParts[2] != "HTTP/1.0" && RequestParts[2] != "HTTP/1.1")
		throw Tools::Exception(EXCEPTION_PARAMS, "Unkown HTTPVersion `" + RequestParts[2] + "`");
	
	const std::string HeaderDelimiter(": ");
	
	AllRequestHeaders.reserve(Lines.size() - 1);
	for(auto LineIterator = Lines.begin() + 1; LineIterator != Lines.end(); LineIterator++)
	{
		size_t ColonPosition = LineIterator->find(HeaderDelimiter);
		if(ColonPosition == std::string::npos)
			continue;
		
		AllRequestHeaders.insert(std::make_pair(LineIterator->substr(0, ColonPosition), LineIterator->substr(ColonPosition + HeaderDelimiter.length())));
	}
	
	URL = RequestParts[1];
	
	try	{ Host = AllRequestHeaders.at("Host"); }
	catch(const std::out_of_range &) { throw Tools::Exception(EXCEPTION_PARAMS, "No Host field present in request"); }
	
	try	{ UserAgent = AllRequestHeaders.at("User-Agent"); }
	catch(const std::out_of_range &) {}
	
	try { IfNoneMatch = AllRequestHeaders.at("If-None-Match"); }
	catch(const std::out_of_range &) {}
	
}

std::string proZPRd::HTTPRequest::GetURL() const
{
	return URL;
}
std::string proZPRd::HTTPRequest::GetHost() const
{
	return Host;
}
std::string proZPRd::HTTPRequest::GetUserAgent() const
{
	return UserAgent;
}
std::string proZPRd::HTTPRequest::GetIfNoneMatch() const
{
	return IfNoneMatch;
}