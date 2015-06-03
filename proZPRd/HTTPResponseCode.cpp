#include "HTTPResponseCode.hpp"

proZPRd::HTTPResponseCode::HTTPResponseCode(unsigned short ResponseCode): ResponseCode(ResponseCode)
{
	
}
unsigned short proZPRd::HTTPResponseCode::GetResponseCode() const
{
	return ResponseCode;
}
std::string proZPRd::HTTPResponseCode::GetContentType() const
{
	return "text/html; charset=UTF-8"
}
std::string proZPRd::HTTPResponseCode::GetContent() const
{
	return "<h1 style=\"text-align: center\">" + std::to_string(ResponseCode) + " " + ResponseCodeToString(ResponseCode) + "</h1>";
}