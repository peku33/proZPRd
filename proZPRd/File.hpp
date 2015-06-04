#pragma once

#include "Tools/NoCreateU.hpp"
#include <string>
#include <vector>

namespace proZPRd
{
	/**
	*	@file
	*	@version 1.0
	*	@class File
	*	@brief Klasa opisująca podstawowe operacje na pliku
	*	
	*	W chwili obecnej zakładam, że będzie zawierała wyłącznie metody statyczne itp, więc nie ma konstruktorów, destruktorów itp. Zabronienie tworzenia obiektów klasy gwarantuje dziedziczenie po NoCreateU
	*/
	class File : public Tools::NoCreateU
	{
		public:
			/**
			*	Metoda ma sprawdzić czy podany plik istnieje i czy jest plikiem.
			*	
			*	@param FileName Nazwa pliku.
			*	@return Jeśli istnieje i jest plikiem - zwraca true. Jeśli nie istnieje lub nie jest plikiem - zwraca false.
			*/
			static bool Exists(const std::string & FileName);
			
			
			/**
			*	Metoda ma wczytać cały plik o podanej nazwie do pamięci i zwrócić go w postaci std::string.
			*	Jeśli plik nie istnieje ma rzucić Tool::Exception z odpowiednimi parametrami
			*	@param FileName Nazwa pliku.
			*	@return Zawartość pliku tekstowego jako std::string.
			*/
			static std::string ToString(const std::string & FileName);
			/**
			*	std::vector<std::string> przechowuje linie pliku tekstowego. 
			*/
			typedef std::vector<std::string> Lines_t;
			/**
			*	Metoda wczytuje cały plik o podanej nazwie do pamięci i zwraca go w postaci Lines_t, czyli wektora zawierającego linie pliku
			*	@param FileName Nazwa pliku. 
			*	@return Zawartość pliku tekstowego z podziałem na linie jako std::vector<std::string>.
			*/
			static Lines_t GetLines(const std::string & FileName);
			
			/**
			*	Struktura reprezentująca plik. Przechowuje nazwę jako Name oraz rozszerzenie jako Extension
			*/
			struct FileStruct
			{
				std::string Name;
				std::string Extension;
			};
			/**
			*	Metoda ma podzielić nazwę pliku na nazwę i rozszerzenie.
			*	Jeśli plik nie ma rozszerzenia, pozostaje ono puste.
			*	@param FileName Nazwa pliku. 
			*	@return Struktura przechowująca nazwę pliku oraz rozszerzenie.
			*/
			static FileStruct SplitFileName(const std::string & FileName);
			
			/**
			*	Metoda pobiera klucz mogący posłużyć do identyfikacji czy nastąpiły zmiany w pliku. W tym konkretnym przypadku kluczem jest data modyfikacji
			*	w postaci unix timestamp.
			*	@param FileName Nazwa pliku. 
			*	@return Zwraca klucz w postaci std::string.
			*/
			static std::string GetETag(const std::string & FileName);
			
			/**
			*	Zamienia ukośniki zgodnie z obecnym systemem operacyjnym.
			*	Windows: / -> \
			*	Pozostałe: \ -> /
			*	
			*	@param Path Ścieżka do pliku. 
			*	@return Zwraca ścieżkę w postaci std::string.
			*/
			static std::string FixSlashes(const std::string & Path);
	};
}