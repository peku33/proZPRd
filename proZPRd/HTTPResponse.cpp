#include "HTTPResponse.hpp"
#include "Tools/Exception.hpp"

std::string proZPRd::HTTPResponse::CreateResponse() const
{
	/// TODO
	return std::string();
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