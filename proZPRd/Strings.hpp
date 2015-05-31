#pragma once

#include "Tools/NoCreateU.hpp"
#include <vector>
#include <string>

namespace proZPRd
{
	/**
		Klasa zawirająca narzędzia służące do obrabiania string'ów
	*/
	class Strings : Tools::NoCreateU
	{
		public:
			typedef std::vector<std::string> StringParts_t;
			/**
				Funkcja służąca do podziału podanego string'a na części według podanego Delimiter'a.
				Zwraca wektor który zawsze będzie zawierał przynajmniej jeden element
			*/
			static StringParts_t SplitString(const std::string & String, const std::string & Delimiter);
	};
}