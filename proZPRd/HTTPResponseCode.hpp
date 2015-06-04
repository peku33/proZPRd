#pragma once

#include "HTTPResponse.hpp"

namespace proZPRd
{
	/**
	*	@file
	*	@version 1.0
	*	@class HTTPResponseCode
	*	@brief Klasa która zwróci stronę zawierającą informację o kodzie błędu.
	*/
	class HTTPResponseCode : public HTTPResponse
	{
		public:
			/**
			*	Konstruktor.
			*	@param ResponseCode - kod błędu.
			*/
			HTTPResponseCode(const unsigned short ResponseCode);
			
		private:
			const unsigned short ResponseCode;
		
		private:
			virtual unsigned short GetResponseCode() const;
			virtual std::string GetContentType() const;
			virtual std::string GetContent() const;
	};
}