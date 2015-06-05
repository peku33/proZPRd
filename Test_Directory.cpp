#include <iostream>
#include "proZPRd/Directory.hpp"

/**
* @brief Testy klasy Directory.
* Wywołane zostaną wszystkie metody klasy Directory. Działanie tych metod zotaje przekierowane na standardowe wyjście.
*/
int main(int ArgC, char ** ArgV)
{
	if(ArgC != 2)
	{
		std::cout << "Usage: " << ArgV[0] << " <FileDataFileName>" << std::endl;
		return 1;
	}

	try
	{
		/**
		*	Test metody Exist.
		*	@return false jesli podana sciezka jest plikiem lub nie istnieje.
		*/
		std::cout << "Exist:" << std::endl;
		std::cout << proZPRd::Directory::Exists(ArgV[1]) << std::endl;

		/**
		*	Test metody List
		*	@return Struktura DirectoryEntries, czyli struktura zawierająca nazwy wszystkich plików i katalogów znajdujących się
		*			w katalogu o podanej ścieżce.
		*/
		proZPRd::Directory::DirectoryEntries DirectoryContent = proZPRd::Directory::List(ArgV[1]);
		std::cout << "List:" << std::endl;
		std::cout << "Directories:" << std::endl;
		for(std::set<std::string>::iterator It = DirectoryContent.Directories.begin(); It != DirectoryContent.Directories.end(); ++It)
			std::cout << *It << std::endl;
		std::cout << "Files:" << std::endl;
		for(std::set<std::string>::iterator It = DirectoryContent.Files.begin(); It != DirectoryContent.Files.end(); ++It)
			std::cout << *It << std::endl;

		/**
		*	Test metody GetDirectorySeparator.
		*	@return znak rozdzielajacy katalogi w zaleznosci od platformy
		*/
		std::cout << "GetDirectorySeparator:" << std::endl;
		std::cout << proZPRd::Directory::GetDirectorySeparator() << std::endl;
	}
	catch(const std::exception & E)
	{
		std::cout << E.what() << std::endl;
	}
	return 0;
}
