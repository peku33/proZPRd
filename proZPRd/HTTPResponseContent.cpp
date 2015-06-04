#include "HTTPResponseContent.hpp"

proZPRd::HTTPResponseContent::HTTPResponseContent(const std::string & Content, const std::string & ContentType, const std::string & ETag): Content(Content), ContentType(ContentType), ETag(ETag)
{
	
}

std::string proZPRd::HTTPResponseContent::GetContentTypeByExtension(const std::string & Extension)
{
	if(Extension == "html" || Extension == "htm")
		return "text/html; charset=UTF-8";
	else if(Extension == "txt")
		return "text/plain";
	else if(Extension == "css")
		return "text/css";
	else if(Extension == "jpg" || Extension == "jpeg")
		return "image/jpeg";
	else if(Extension == "gif")
		return "image/gif";
	else if(Extension == "png")
		return "image/png";
	else if(Extension == "ico")
		return "image/x-icon";
	else if(Extension == "js")
		return "application/javascript";
	
	return "application/octet-stream";
}

unsigned short proZPRd::HTTPResponseContent::GetResponseCode() const
{
	return 200;
}
std::string proZPRd::HTTPResponseContent::GetETag() const
{
	return ETag;
}
std::string proZPRd::HTTPResponseContent::GetContentType() const
{
	return ContentType;
}
std::string proZPRd::HTTPResponseContent::GetContent() const
{
	return Content;
}