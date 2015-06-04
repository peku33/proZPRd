#pragma once

#include <string>

#define EXCEPTION_PARAMS __PRETTY_FUNCTION__, __FILE__, __LINE__

namespace proZPRd
{
	namespace Tools
	{
		/**
		*	@file
		*	@version 1.0
		*	@class Exception
		*	@brief Domyślna klasa wyjątków z której będziemy korzystać.
		*
		*	Makro EXCEPTION_PARAMS powoduje uzupełnienie trzech pierwszych parametrów automatycznymi wartościami.
		*	Do uzupełnienia pozostaje ostatni - czwarty parametr Message w którym piszemy wiadomość związaną z rzucanym wyjątkiem.
		*	
		*	Użycie:
		*	
		*	(...)
		*	throw Tools::Exception(EXCEPTION_PARAMS, "Wystapil straszny blad!");
		*	(...)
		*/
		class Exception : public std::exception
		{
			public:
			/**
			*	Konstruktor klasy Exception.
			*	@param FileName - Plik
			*	@param Line - Numer lini
			*	@param Message - Wiadomosc
			*/
				Exception(const std::string & PrettyFunction, const std::string & FileName, const unsigned int Line, const std::string & Message);
				virtual ~Exception();
				
			private:
				std::string AsString;
			
			public:
			/**
			*	Metoda tworząca komunikat wyjątku w postaci std::string.
			*	@return Zwraca wyjątek w postaci std::string.
			*/
			const std::string ToString() const;
			
			/**
			*	Metoda tworząca kominikat wyjątku tablicy znaków.
			*	@return Zwraca wskaźnik do tablicy znaków.
			*/
			virtual const char * what() const noexcept;
		};
	}
}