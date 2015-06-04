#pragma once

#include "Tools/NoCreateU.hpp"
#include <vector>
#include <string>

namespace proZPRd
{
	/**
	*	@file
	*	@version 1.0
	*	@class Strings
	*	Klasa zawierająca narzędzia służące do obrabiania string'ów
	*/
	class Strings : Tools::NoCreateU
	{
		public:
			typedef std::vector<std::string> StringParts_t;
			/**
			*	Funkcja służąca do podziału podanego string'a na części według podanego Delimiter'a.
			*	@param String String do podziału.
			*	@param Delimiter Znak po którym dzielimy.
			*	@return Zwraca wektor który zawsze będzie zawierał przynajmniej jeden element
			*/
			static StringParts_t SplitString(const std::string & String, const std::string & Delimiter);
	};
}