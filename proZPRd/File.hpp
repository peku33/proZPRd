#pragma once

#include "Tools/NoCreateU.hpp"
#include <string>
#include <vector>

namespace proZPRd
{
	/**
		Klasa opisująca podstawowe operacje na pliku
		
		W chwili obecnej zakładam, że będzie zawierała wyłącznie metody statyczne itp, więc nie ma konstruktorów, destruktorów itp. Zabronienie tworzenia obiektów klasy gwarantuje dziedziczenie po NoCreateU
	*/
	class File : public Tools::NoCreateU
	{
		public:
		
			typedef std::vector<std::string> Lines_t;
			
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
			
			/**
				Funkcja wczytuje cały plik o podanej nazwie do pamięci i zwraca go w postaci Lines_t, czyli wektora zawierającego linie pliku
			*/
			
			static Lines_t GetLines(const std::string & FileName);
			
			struct FileStruct
			{
				std::string Name;
				std::string Extension;
			};
			/**
				Funkcja ma podzielić nazwę pliku na nazwę i rozszerzenie.
				Jeśli plik nie ma rozszerzenia, pozostaje ono puste.
			*/
			static FileStruct SplitFileName(const std::string & FileName);
			
	};
}