#pragma once

#include <memory>
#include <string>

namespace proZPRd
{	
	/**
	*	@file
	*	@version 1.0
	*	@class HTTPResponse
	* 	Klasa zwracająca odpowiedź na zapytanie HTTP. 
	*/
	class HTTPResponse
	{
		public:
			typedef std::unique_ptr<HTTPResponse> HTTPResponsePtr;
			
			/**
			*	Metoda przekszałcająca dane z własnych informacji oraz wyników funkcji wirtualnych na pełny ciąg który zostanie odesłany klientowi jako odpowiedź
			*	@return Zwraca odpowiedź w postaci std::string.
			*/
			std::string CreateResponse() const;
		
		protected:
			/**
			*	Statyczna metoda zamieniająca kod odpowiedzi HTTP na jego postać tekstową
			*	@return Zwraca odpowiedź w postaci std::string.
			*/
			static std::string ResponseCodeToString(const unsigned short ResponseCode);
		
		private:
			static std::string GenerateHTTPDate();
			
		private:
			/**
			*	Metoda zwracająca kod odpowiedzi HTTP
			*	@return Zwraca kod odpowiedzi. 
			*/
			virtual unsigned short GetResponseCode() const = 0;
			
			/**
<<<<<<< HEAD
			*	Metoda zwracająca zawartość nagłówka Content-Type
			*	@return Zwraca zawartość nagłówka Content-Type jako std::string.
=======
				Metoda zwracająca ETag dla treści.
				Domyślnie nie ma ETag'u - nieprzeciążona funkcja zwraca pustą wartość
			*/
			virtual std::string GetETag() const;
			
			/**
				Metoda zwracająca zawartość nagłówka Content-Type
>>>>>>> origin/master
			*/
			virtual std::string GetContentType() const = 0;
			
			/**
			*	Metoda zwracająca dodatkowe nagłówki które mają zostać.
			*/
			virtual std::string GetContent() const = 0;
	};
}