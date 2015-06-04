#pragma once

#include <string>
#include <unordered_map>

namespace proZPRd
{
	/**
	*	@file
	*	@version 1.0
	*	@class HTTPRequest
	*	Klasa parsująca otrzymane zapytania HTTP, umożliwiająca ich łatwą obsługę.
	*/
	class HTTPRequest
	{
		public:
			class HTTPRequestNotComplete{ };
			static HTTPRequest TryParse(const std::string & Request);
			
		public:
			/**
			*	Konstruktor przyjmuje w argumentach wywołania zapytanie HTTP i przypisuje dane z niego do odpowiednich zmiennych klasy.
			*	@param Request Zapytanie HTTP.
			*/
			HTTPRequest(const std::string & Request);
		private:
			std::unordered_map<std::string, std::string> AllRequestHeaders;
		
			std::string URL;
			std::string Host;
			std::string UserAgent;
			std::string RequestedETag;
		
		public:
			/**
			*	@return Metoda zwraca URL.
			*/
			std::string GetURL() const;
			/**
			*	@return Metoda zwraca Host.
			*/
			std::string GetHost() const;
			/**
			*	@return Metoda zwraca nazwę aplikacji klienckiej HTTP.
			*/
			std::string GetUserAgent() const;
			/**
			*	@return Metoda zwraca entity tag.
			*/
			std::string GetRequestedETag() const;
	};
}