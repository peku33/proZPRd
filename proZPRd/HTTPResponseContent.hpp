#pragma once

#include "HTTPResponse.hpp"

namespace proZPRd
{
	class HTTPResponseContent : public HTTPResponse
	{
		public:
			HTTPResponseContent(const std::string & Content, const std::string & ContentType, const std::string & ETag);
			
		private:
			const std::string Content;
			const std::string ContentType;
			const std::string ETag;
		
		public:
			static std::string GetContentTypeByExtension(const std::string & Extension);
		
		private:
			virtual unsigned short GetResponseCode() const;
			virtual std::string GetETag() const;
			virtual std::string GetContentType() const;
			virtual std::string GetContent() const;
	};
}