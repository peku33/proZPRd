#pragma once

#include "HTTPResponse.hpp"

namespace proZPRd
{
	/**
	*	Klasa opisująca odpowiedź serwera zawierającą treść
	*/
	class HTTPResponseContent : public HTTPResponse
	{
		public:
			/**
			*	Konstruktor.
			*	
			*	Content - właściwa zawartość treści
			*	ContentType - wartość nagłówka Content-Type, wygenerowana na przykład poprzez GetContentTypeByExtension
			*	ETag - zawartość nagłówka ETag. Jeśli .empty() - nagłówek nie zostanie wysłany
			*/
			HTTPResponseContent(const std::string & Content, const std::string & ContentType, const std::string & ETag);
			
		private:
			const std::string Content;
			const std::string ContentType;
			const std::string ETag;
		
		public:
			/**
			* Generuje zawartość nagłówka Content-Type na podstawie rozszerzenia.
			* Posiada wewnętrzną bazę rozszerzeń
			* W przypadku braku dopasowania zwraca domyślną wartość
			*/
			static std::string GetContentTypeByExtension(const std::string & Extension);
		
		private:
			virtual unsigned short GetResponseCode() const;
			virtual std::string GetETag() const;
			virtual std::string GetContentType() const;
			virtual std::string GetContent() const;
	};
}