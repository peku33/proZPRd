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
	return "text/html; charset=UTF-8";
}
std::string proZPRd::HTTPResponseCode::GetContent() const
{
	return "<!DOCTYPE html><html><body style=\"text-align: center\"><h1>" + std::to_string(ResponseCode) + " " + ResponseCodeToString(ResponseCode) + "</h1><hr>proZPRd</body></html>";
}