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
	*	@brief Klasa zawierająca narzędzia służące do obrabiania string'ów
	*/
	class Strings : public Tools::NoCreateU
	{
		public:
			/**
			*	std::vector<std::string> Wektor przechowujący substringi, po podzieleniu.
			*/
			typedef std::vector<std::string> StringParts_t;
			
			/**
			*	Funkcja służąca do podziału podanego string'a na części według podanego Delimiter'a.
			*	@param String String do podziału.
			*	@param Delimiter Znak po którym dzielimy.
			*	@return Zwraca wektor który zawsze będzie zawierał przynajmniej jeden element
			*/
			static StringParts_t SplitString(const std::string & String, const std::string & Delimiter);
			
			/**
			*	Funkcja usunie wszystkie białe znaki z początku i końca stringu
			*	@param String String wejściowy
			*	@return Napis z usuniętymi znakami
			*/
			static std::string Trim(const std::string & String);
	};
}
