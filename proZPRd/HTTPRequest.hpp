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
				Konstruktor przyjmuje w argumentach wywołania zapytanie HTTP i przypisuje dane z niego do odpowiednich zmiennych klasy.
			*/
			HTTPRequest(const std::string & Request);
			
		private:
			std::unordered_map<std::string, std::string> AllRequestHeaders;
		
			std::string URL;
			std::string Host;
			std::string UserAgent;
			std::string RequestedETag;
		
		public:
			class HTTPRequestNotComplete{ };

			static HTTPRequest TryParse(const std::string & Request);
			std::string GetURL() const;
			std::string GetHost() const;
			std::string GetUserAgent() const;
			std::string GetRequestedETag() const;
	};
}