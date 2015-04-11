#pragma once

#include "Tools/NoCreateU.hpp"
#include "Tools/Exception.hpp"
#include <string>
#include <set>
#include <dirent.h>

namespace proZPRd
{
	/**
		Klasa do obsługi podstawowych rzeczy związanych z katalogami.
		Ponieważ nie istnieją póki co obiekty tej klasy - domyślnie dziedziczy ona po NoCreateU, który nie pozwala na ich utworzenie
	*/
	class Directory : public Tools::NoCreateU
	{
		public:
			/**
				Funkcja ma sprawdzić, czy katalog o podanej nazwie istnieje i czy jest katalogiem.
				Jeśli nie istnieje - zwraca false
				Jeśli nie jest katalogiem - zwraca false
				A tak to zwraca true
			*/
			static bool Exists(const std::string & DirectoryName);
			
			
			/**
				Funkcja ma wczytać wszystkie pliki i katalogi które znajdują się w danym katalogu i zwrócić je w postaci struktury poniżej.
				
				W secie Directory znajdują się katalogi, w Files pliki. Sortowanie zapewnia sam kontener.
				
				W razie wystąpienia błędu ma rzucać standardowy wyjątek Tools::Exception
			*/
			struct DirectoryEntries
			{
				std::set<std::string> Directories;
				std::set<std::string> Files;
			};
			static DirectoryEntries List(const std::string & DirectoryName);
	};
}