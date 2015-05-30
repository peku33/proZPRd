#pragma once

#include <string>

namespace proZPRd
{
	/**
		Klasa parsująca otrzymane zapytania HTTP, umożliwiająca ich łatwą obsługę.
	*/
	class HTTPRequest
	{		
		private:
			std::string URL;
			std::string Host;
			std::string UserAgent;
		
		public:
			/**
				Konstruktor przyjmuje w argumentach wywołania zapytanie HTTP i przypisuje dane z niego do odpowiednich zmiennych klasy.
			*/
			HTTPRequest(const std::string & Request);
			std::string GetURL() {return URL;};
			std::string GetHost() {return Host;};
			std::string GetUserAgent() {return UserAgent;};
	};
}