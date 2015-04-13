#pragma once

#include <string>

#define EXCEPTION_PARAMS __PRETTY_FUNCTION__, __FILE__, __LINE__

namespace proZPRd
{
	namespace Tools
	{
		/**
			Domyślna klasa wyjątków z której będziemy korzystać.
			Makro EXCEPTION_PARAMS powoduje uzupełnienie trzech pierwszych parametrów automatycznymi wartościami.
			Do uzupełnienia pozostaje ostatni - czwarty parametr Message w którym piszemy wiadomość związaną z rzucanym wyjątkiem.
			
			Użycie:
			
			(...)
			throw Tools::Exception(EXCEPTION_PARAMS, "Wystapil straszny blad!");
			(...)
		*/
		class Exception : public std::exception
		{
			public:
				Exception(const std::string & PrettyFunction, const std::string & File, const unsigned int Line, const std::string & Message);
				virtual ~Exception();
				
			private:
				const std::string PrettyFunction;
				const std::string File;
				const unsigned int Line;
				const std::string Message;
			
			public:
				const std::string ToString() const;
				virtual const char * what() const noexcept;
		};
	}
}