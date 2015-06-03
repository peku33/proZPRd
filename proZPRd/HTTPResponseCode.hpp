#pragma once

#include "HTTPResponse.hpp"

namespace proZPRd
{
	/**
		Klasa która zwróci stronę zawierającą informację o kodzie błędu.
	*/
	class HTTPResponseCode : public HTTPResponse
	{
		public:
			HTTPResponseCode(const unsigned short ResponseCode);
			
		private:
			const unsigned short ResponseCode;
		
		private:
			virtual unsigned short GetResponseCode() const;
			virtual std::string GetContentType() const;
			virtual std::string GetContent() const;
	};
}