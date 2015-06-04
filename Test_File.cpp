#include <iostream>
#include "proZPRd/File.hpp"

/**
* @brief Testy klasy File. 
* Wywołane zostaną wszystkie metody klasy File. Działanie tych metod zotaje przekierowane na standardowe wyjście.
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
		*	@return true jeśli plik istnieje.
		*/
		std::cout << "Exist:" << std::endl; 
		std::cout << proZPRd::File::Exists(ArgV[1]) << std::endl;
		
		/**
		*	Test metody ToString.
		*	@return Zawartość pliku tekstowego jako std::string.
		*/
		auto FileContent = proZPRd::File::ToString(ArgV[1]);
		std::cout << "ToString: "<< std::endl; 
		std::cout << FileContent << std::endl;
		
		/**
		*	Test metody GetLines.
		*	@return Zawartość pliku tekstowego z podziałem na linie jako std::vector<std::string>.
		*/
		std::vector<std::string> Lines = proZPRd::File::GetLines(ArgV[1]);
		std::cout << "GetLines: "<< std::endl; 
		for(std::string It : Lines)
		{
			std::cout << It << std::endl;
		}
		
		/**
		*	Test metody SplitFileName. Metoda ta dzieli nazwę pliku na nazwę oraz rozerzenie
		*	@return Struktura przechowująca nazwę pliku oraz rozszerzenie.
		*/
		proZPRd::File::FileStruct FS = proZPRd::File::SplitFileName(ArgV[1]);
		std::cout << "SplitFileName: "<< std::endl; 
		std::cout << "Filename: " << FS.Name << " Extension: " << FS.Extension << std::endl;
		
		/**
		*	Test metody GetETag. 
		*	Zwraca klucz mogący posłużyć do identyfikacji czy nastąpiły zmiany w pliku. W tym konkretnym przypadku kluczem jest data modyfikacji w postaci unix timestamp
		*/
		std::string ETag = proZPRd::File::GetETag(ArgV[1]);
		std::cout << "ETag: " << ETag << std::endl;
	}
	catch(const std::exception & E)
	{
		std::cout << E.what() << std::endl;
	}
	return 0;
}