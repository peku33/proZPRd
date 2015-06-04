#pragma once

#include <string>
#include <unordered_map>

namespace proZPRd
{
	/**
		Klasa parsująca otrzymane zapytania HTTP, umożliwiająca ich łatwą obsługę.
	*/
	class HTTPRequest
	{
		public:
			/**
				Wyjątek rzucany przez metodę TryParse oznaczający, że Request nie jest jeszcze kompletny i potrzebna jest większa ilość danych
			*/
			class HTTPRequestNotComplete{ };
			
			/**
				Statyczna metoda tworząca obiekt tej klasy na podstawie czegoś, co powinno być zapytaniem.
				Możliwe (i nawet na pewnym etapie konieczne) będzie podawanie jako argumentu danych otrzymanych od kliena, które niekoniecznie muszą stanowić pełne zapytanie (nigdy nie wiemy, czy klient skończył nadawać, czy nie)
				Jeśli ilość danych jest wystarczająca - metoda zwróci obiekt tej klasy, jeśli nie - rzuci powyższy wyjątek.
			*/
			static HTTPRequest TryParse(const std::string & Request);
			
		public:
			/**
				Konstruktor przyjmuje w argumentach wywołania zapytanie HTTP i przypisuje dane z niego do odpowiednich zmiennych klasy.
				Na tym etapie musi to być kompletne zapytanie
			*/
			HTTPRequest(const std::string & Request);
			
		private:
			/**
				Mapa przechowująca wszystkie elementy przysłane przez klienta
			*/
			std::unordered_map<std::string, std::string> AllRequestHeaders;
			
			std::string URL;
			std::string Host;
			std::string UserAgent;
			std::string RequestedETag;
		
		public:
			std::string GetURL() const;
			std::string GetHost() const;
			std::string GetUserAgent() const;
			std::string GetRequestedETag() const;
	};
}