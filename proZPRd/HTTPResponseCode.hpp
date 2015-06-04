#pragma once

#include "HTTPResponse.hpp"

namespace proZPRd
{
	/**
	*	@file
	*	@version 1.0
	*	@class HTTPResponseCode
	*	Klasa która zwróci stronę zawierającą informację o kodzie błędu.
	*/
	class HTTPResponseCode : public HTTPResponse
	{
		public:
			HTTPResponseCode(const unsigned short ResponseCode);
			
		private:
			const unsigned short ResponseCode;
		
		private:
			/**
			*	Metoda zwracająca kod odpowiedzi HTTP
			*	@return Zwraca kod odpowiedzi. 
			*/
			virtual unsigned short GetResponseCode() const;
			/**
			*	Metoda zwracająca zawartość nagłówka Content-Type
			*	@return Zwraca zawartość nagłówka Content-Type jako std::string.
			*/
			virtual std::string GetContentType() const;
			/**
			*	Metoda zwracająca dodatkowe nagłówki które mają zostać.
			*/
			virtual std::string GetContent() const;
	};
}