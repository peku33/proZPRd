#pragma once

#include "HTTPResponse.hpp"

namespace proZPRd
{
	/**
	*	@file
	*	@version 1.0
	*	@class HTTPResponseNotModified
	*	@brief Klasa opisująca odpowiedź HTTP 304 Not Modified
	*/
	class HTTPResponseNotModified : public HTTPResponse
	{
		public:
		/**
		*	Konstruktor.
		*/
			HTTPResponseNotModified();
		
		private:
			virtual unsigned short GetResponseCode() const;
			virtual std::string GetContentType() const;
			virtual std::string GetContent() const;
	};
}