#pragma once

#include "Tools/NoCreateU.hpp"
#include <string>

namespace proZPRd
{
	/**
		Klasa opisująca podstawowe operacje na pliku
		
		W chwili obecnej zakładam, że będzie zawierała wyłącznie metody statyczne itp, więc nie ma konstruktorów, destruktorów itp. Zabronienie tworzenia obiektów klasy gwarantuje dziedziczenie po NoCreateU
	*/
	class File : public Tools::NoCreateU
	{
		public:
			/**
				Funkcja ma sprawdzić czy podany plik istnieje i czy jest plikiem.
				
				Jeśli istnieje i jest plikiem - zwraca true
				Jeśli nie istnieje lub nie jest plikiem - zwraca false
			*/
			static bool Exists(const std::string & FileName);
			
			
			/**
				Funkcja ma wczytać cały plik o podanej nazwie do pamięci i zwrócić go w postaci std::string.
				Jeśli plik nie istnieje ma rzucić Tool::Exception z odpowiednimi parametrami
			*/
			static std::string ToString(const std::string & FileName);
	};
}