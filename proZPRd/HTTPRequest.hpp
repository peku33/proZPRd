#pragma once

#include <string>
#include <unordered_map>

namespace proZPRd
{
	/**
	*	@file
	*	@version 1.0
	*	@class HTTPRequest
	*	@brief Klasa parsująca otrzymane zapytania HTTP, umożliwiająca ich łatwą obsługę.
	*/
	class HTTPRequest
	{
		public:
			/**
			*	@brief Wyjątek rzucany przez metodę TryParse. 
			*	
			*	Oznaczający, że Request nie jest jeszcze kompletny i potrzebna jest większa ilość danych
			*/
			class HTTPRequestNotComplete{ };
			
			/**
			*	Statyczna metoda tworząca obiekt tej klasy na podstawie czegoś, co powinno być zapytaniem.
			*	Możliwe (i nawet na pewnym etapie konieczne) będzie podawanie jako argumentu danych otrzymanych od kliena, które niekoniecznie muszą stanowić pełne zapytanie (nigdy nie wiemy, czy klient skończył nadawać, czy nie)
			*	Jeśli ilość danych jest wystarczająca - metoda zwróci obiekt tej klasy, jeśli nie - rzuci powyższy wyjątek.
			*	@param Request zapytanie w postaci std::string.
			*/
			static HTTPRequest TryParse(const std::string & Request);
			
		public:
			/**
			*	Konstruktor przyjmuje w argumentach wywołania zapytanie HTTP i przypisuje dane z niego do odpowiednich zmiennych klasy.
			*	@param Request Zapytanie HTTP.
			*	Na tym etapie musi to być kompletne zapytanie
			*/
			HTTPRequest(const std::string & Request);
			
		private:
			/**
			*	Mapa przechowująca wszystkie elementy przysłane przez klienta.
			*/
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