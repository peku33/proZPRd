#pragma once

#include "Tools/NoCreateU.hpp"
#include <string>
#include <mutex>

namespace proZPRd
{
	/**
		
		Klasa służąca do ładnego wypisawania do konsoli. Zawiera 4 typy wiadomości: Ok, Info, Warning, Error które będą różniły się między sobą prefixem / kolorem wyświetlanej wiadomości
		
		Zawiera wyłącznie metody statyczne
		
	*/
	class Logger : public Tools::NoCreateU
	{
		public:
			///Wysyła do konsoli informację o sukcesie
			static void Ok(const std::string & Message);
			
			///Wysyła do konsoli informację
			static void Info(const std::string & Message);
			
			///Wysyła do konsoli ostrzeżenie
			static void Warning(const std::string & Message);
			
			///Wysyła do konsoli informacje o błędzie
			static void Error(const std::string & Message);
		
		private:
			/**
				Typ wyliczeniowy służący do przekazywania rodzaju wiadomości do docelowej funkcji Display
			*/
			enum class MessageType
			{
				OK,
				INFO,
				WARNING,
				ERROR
			};
			
			/**
				Właściwa funkcja która wyświetla napisy.
				Jako argumenty przyjmuje treść wiadomości i jej typ
			*/
			static void Display(const std::string & Message, const MessageType MT);
			
			/**
				Funkcja konwertująca typ wiadomości do słownego opisu
			*/
			static std::string MessageTypeToString(const MessageType MT); 
	};
}