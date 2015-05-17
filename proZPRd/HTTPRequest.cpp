#include "HTTPRequest.hpp"
#include "Tools/Exception.hpp"


proZPRd::HTTPRequest::HTTPRequest(const std::string & Request)
{
	unsigned URLEnd;
	if((URLEnd = Request.find(" ", 4)) == std::string::npos)
		throw Tools::Exception(EXCEPTION_PARAMS, "HTTP request format error: URL not found");
	
	URL = Request.substr(4, URLEnd - 4);
	
	unsigned HostPos;
	if((HostPos = Request.find("Host:")) == std::string::npos)
		throw Tools::Exception(EXCEPTION_PARAMS, "HTTP request format error: Host not found");
	
	unsigned HostEnd;
	if((HostEnd = Request.find("\r\n", HostPos)) == std::string::npos)
		throw Tools::Exception(EXCEPTION_PARAMS, "HTTP request format error: bad format");
	
	Host = Request.substr(HostPos + 6, HostEnd - HostPos - 6);
	
	unsigned UserAgentPos;
	if((UserAgentPos = Request.find("UserAgent:")) != std::string::npos)
	{
		unsigned UserAgentEnd;
		if((UserAgentEnd = Request.find("\r\n", UserAgentPos)) == std::string::npos)
			throw Tools::Exception(EXCEPTION_PARAMS, "HTTP request format error: bad format");
		
		UserAgent = Request.substr(UserAgentPos + 11, UserAgentEnd - UserAgentPos - 11);
	}
} 