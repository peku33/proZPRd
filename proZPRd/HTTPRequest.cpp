#include "HTTPRequest.hpp"
#include "Tools/Exception.hpp"
#include <iostream>


proZPRd::HTTPRequest::HTTPRequest(const std::string & Request)
{
	Lines_t Buffer = toLines_t(Request);
	
	if(Buffer[0].substr(0, 3) != "GET")
		throw Tools::Exception(EXCEPTION_PARAMS, "HTTP request format error!");
	
	if(Buffer[0].find(" ", 4) == std::string::npos)
		throw Tools::Exception(EXCEPTION_PARAMS, "HTTP request format error: Bad URL format! ")
	
	URL = Buffer[0].substr(4, Buffer[0].find(" ", 4) - 4);
	
	Host = Find(Buffer, "Host");
	
	if(Host.empty())
		throw Tools::Exception(EXCEPTION_PARAMS, "HTTP request format error: Host not found!");
	
	UserAgent = Find(Buffer, "UserAgent");
	
}

proZPRd::HTTPRequest::Lines_t proZPRd::HTTPRequest::toLines_t(const std::string & Request)
{
	Lines_t Buffer;
	unsigned int Position = 0;
	unsigned int Temp;
		
	while((Temp = Request.find("\r", Position)) != std::string::npos)
	{	
		Buffer.push_back(Request.substr(Position, Temp - Position));
		Position = Temp + 2; //Przesuwamy wskaznik w stringu za znaki \r\n
	}
	
	return Buffer;
}

std::string proZPRd::HTTPRequest::Find(const Lines_t & Request, const std::string & Header)
{
	unsigned int i;
	unsigned int Position;
	unsigned int Size = Request.size();
	
	for(i = 1; i < Size; ++i) //Pozycja 0 nas nie interesuje
	{
		if((Position = Request[i].find(": ")) != std::string::npos)
		{
			if(Request[i].substr(0, Position) == Header)
				return Request[i].substr(Position + 2); // +3 zeby zaczac dzielic stringa od pierwszego znaku za ": "
		}
	}
	
	return "";
}