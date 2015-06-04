#pragma once

#include "HTTPResponse.hpp"

namespace proZPRd
{
	/**
	*	@file
	*	@version 1.0
	*	@class HTTPResponseContent
	*	@brief Klasa opisująca odpowiedź serwera zawierającą treść
	*/
	class HTTPResponseContent : public HTTPResponse
	{
		public:
			/**
			*	Konstruktor.
			*	@param Content - właściwa zawartość treści
			*	@param ContentType - wartość nagłówka Content-Type, wygenerowana na przykład poprzez GetContentTypeByExtension
			*	@param ETag - zawartość nagłówka ETag. Jeśli .empty() - nagłówek nie zostanie wysłany
			*/
			HTTPResponseContent(const std::string & Content, const std::string & ContentType, const std::string & ETag);
			
		private:
			const std::string Content;
			const std::string ContentType;
			const std::string ETag;
		
		public:
			/**
			*	Generuje zawartość nagłówka Content-Type na podstawie rozszerzenia.
			*	Posiada wewnętrzną bazę rozszerzeń
			*	W przypadku braku dopasowania zwraca domyślną wartość
			*	@param Extension Rozszerzenie pliku. 
			*	@return Zwraca zawartość w postaci std::string.
			*/
			static std::string GetContentTypeByExtension(const std::string & Extension);
		
		private:
			virtual unsigned short GetResponseCode() const;
			virtual std::string GetETag() const;
			virtual std::string GetContentType() const;
			virtual std::string GetContent() const;
	};
}