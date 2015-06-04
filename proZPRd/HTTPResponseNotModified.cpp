#include "HTTPResponseNotModified.hpp"

proZPRd::HTTPResponseNotModified::HTTPResponseNotModified()
{
	
}
unsigned short proZPRd::HTTPResponseNotModified::GetResponseCode() const
{
	return 304;
}
std::string proZPRd::HTTPResponseNotModified::GetContentType() const
{
	return std::string();
}
std::string proZPRd::HTTPResponseNotModified::GetContent() const
{
	return std::string();
}