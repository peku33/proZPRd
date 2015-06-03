#pragma once

#include <string>

namespace proZPRd
{
	class HTTPResponse
	{
		public:
			/**
				Metoda przekszałcająca dane z własnych informacji oraz wyników funkcji wirtualnych na pełny ciąg który zostanie odesłany klientowi jako odpowiedź
			*/
			std::string CreateResponse() const;
		
		protected:
			/**
				Statyczna metoda zamieniająca kod odpowiedzi HTTP na jego postać tekstową
			*/
			static std::string ResponseCodeToString(const unsigned short ResponseCode);
			
		private:
			/**
				Metoda zwracająca kod odpowiedzi HTTP
			*/
			virtual unsigned short GetResponseCode() const = 0;
			
			/**
				Metoda zwracająca zawartość nagłówka Content-Type
			*/
			virtual std::string GetContentType() const = 0;
			
			/**
				Metoda zwracająca dodatkowe nagłówki które mają zosta
			*/
			virtual std::string GetContent() const = 0;
	};
}