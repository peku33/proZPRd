#pragma once

#include "HTTPResponse.hpp"

namespace proZPRd
{
	/**
	*	Klasa opisująca odpowiedź HTTP 304 Not Modified
	*/
	class HTTPResponseNotModified : public HTTPResponse
	{
		public:
			HTTPResponseNotModified();
		
		private:
			virtual unsigned short GetResponseCode() const;
			virtual std::string GetContentType() const;
			virtual std::string GetContent() const;
	};
}