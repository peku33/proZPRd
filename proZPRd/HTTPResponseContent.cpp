#include "HTTPResponseContent.hpp"

proZPRd::HTTPResponseContent::HTTPResponseContent(const std::string & Content, const std::string & ContentType, const std::string & ETag): Content(Content), ContentType(ContentType), ETag(ETag)
{
	
}

std::string proZPRd::HTTPResponseContent::GetContentTypeByExtension(const std::string & Extension)
{
	/// TODO - uzupełnić dla typów: jpg, jpeg, gif, png, ico, js, txt, html (oraz htm), css
	
	if(Extension == "html" || Extension == "htm")
		return "text/html; charset=UTF-8";
	
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