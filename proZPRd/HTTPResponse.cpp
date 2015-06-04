#include "HTTPResponse.hpp"

#include "Tools/Exception.hpp"
#include <time.h>

std::string proZPRd::HTTPResponse::CreateResponse() const
{
	const unsigned short ResponseCode = GetResponseCode();
	const std::string ResponseCodeString = ResponseCodeToString(ResponseCode);
	const std::string ETag = GetETag();
	const std::string ContentType = GetContentType();
	const std::string Content = GetContent();
	const size_t ContentLength = Content.length();
	
	std::string Response;
	
								Response.append("HTTP/1.1 " + std::to_string(ResponseCode) + " " + ResponseCodeString + "\r\n");
								Response.append("Date: " + GenerateHTTPDate() + "\r\n");
	if(!ETag.empty())			Response.append("ETag: W/\"" + ETag + "\"\r\n");
	if(!ContentType.empty())	Response.append("Content-Type: " + ContentType + "\r\n");
	if(ContentLength > 0)		Response.append("Content-Length: " + std::to_string(ContentLength) + "\r\n");
								Response.append("Connection: close\r\n");
								Response.append("Server: proZPRd\r\n");
								Response.append("\r\n");
	if(!Content.empty())		Response.append(Content);
	
	return Response;
}

std::string proZPRd::HTTPResponse::ResponseCodeToString(const unsigned short ResponseCode)
{
	switch(ResponseCode)
	{
		case 200:
			return "OK";
		case 204:
			return "No content";
		case 301:
			return "Moved Permanently";
		case 302:
			return "Found";
		case 304:
			return "Not Modified";
		case 400:
			return "Bad Request";
		case 403:
			return "Forbidden";
		case 404:
			return "Not Found";
		case 500:
			return "Internal Server Error";
		default:
			throw Tools::Exception(EXCEPTION_PARAMS, "Unknown response code!");
	}
}

std::string proZPRd::HTTPResponse::GenerateHTTPDate()
{
	char Date[128];
	time_t Now = time(NULL);
	struct tm * DateStruct = gmtime(&Now);
	auto Length = strftime(Date, sizeof(Date), "%a, %d %b %Y %H:%M:%S %Z", DateStruct);
	return std::string(Date, Length);
}

std::string proZPRd::HTTPResponse::GetETag() const
{
	return std::string();
}