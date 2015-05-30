#pragma once

#include <string>
#include <vector>

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
			
			/**
				Metoda przyjmuje w argumentach wywołania zapytanie HTTP, rozbija je na stringi przechowujace pojedyncze linie i dodaje do wektora
			*/
			typedef std::vector<std::string> Lines_t;
			Lines_t toLines_t(const std::string & Request);
			
			/**
				Metoda odszukuje w wektorze pola zaczynajacego sie od naglowka przekazanego w argumencie wywolania. W przypadku odnalezienia
				pola, metoda zwraca jego zawartosc tzn wszystko co znajduje sie za naglowkiem. Jesli pole nie zostaje odnalezione, metoda
				zwraca pusty string
			*/
			std::string Find(const Lines_t & Request, const std::string & Header);
			
			std::string GetURL() {return URL;};
			std::string GetHost() {return Host;};
			std::string GetUserAgent() {return UserAgent;};
	};
}