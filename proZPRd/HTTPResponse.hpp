#pragma once

#include <memory>
#include <string>

namespace proZPRd
{
	class HTTPResponse
	{
		public:
			typedef std::unique_ptr<HTTPResponse> HTTPResponsePtr;
			
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
			static std::string GenerateHTTPDate();
			
		private:
			/**
				Metoda zwracająca kod odpowiedzi HTTP
			*/
			virtual unsigned short GetResponseCode() const = 0;
			
			/**
				Metoda zwracająca ETag dla treści.
				Domyślnie nie ma ETag'u - nieprzeciążona funkcja zwraca pustą wartość
			*/
			virtual std::string GetETag() const;
			
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