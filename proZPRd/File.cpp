#include "File.hpp"

#include <stdio.h>
#include <string>
#include <sys/stat.h>
#include <fstream>
#include "Tools/Exception.hpp"

bool proZPRd::File::Exists(const std::string & FileName)
{
	struct stat S;
	return (stat(FileName.c_str(), &S) == 0) && S_ISREG(S.st_mode);
}

std::string proZPRd::File::ToString(const std::string & FileName)
{
	/*
		Flaga r powoduje otwarcie tylko do odczytu. Wszystkie inne flagi proszą o dostęp z zapisem. Stosując tylko flagę r umożliwiamy sobie odczyt pliku który jest chroniony, tylko do odczytu itp. Ponadto umożliwiamy równoległy dostęp.
		Flaga b powoduje otwarcie pliku w trybie binarnym. Dzięki temu nie będzie konwersji znaku końca lini, co jest bardzo niepożądane w plikach z danymi.
	*/
	
	FILE * F = fopen(FileName.c_str(), "rb");
	if(F == NULL)
		throw Tools::Exception(EXCEPTION_PARAMS, "fopen() failed...");
	
	/*
		Ustawiamy rozmiar cegiełki na 512b.
	*/
	const unsigned int BufferSize = 512;
	char Buffer[BufferSize];
	std::string Output;
	
	/*
		Czytamy dopóki nie przeczytamy całości, nic innego nas nie interesuje.
	*/
	
	while(!feof(F))
	{
		unsigned int BytesRead = fread(Buffer, sizeof(char), BufferSize, F);
		if(BytesRead <= 0)
		{
			/*
				Jeśli wystąpił błąd, przed rzuceniem wyjątku zamykamy plik, inaczej pozostanie otwarty na zawsze
			*/
			fclose(F);
			throw Tools::Exception(EXCEPTION_PARAMS, "fread() failed...");
		}
		
		/*
			Dopisujemy do wyjścia DOKŁADNIE tyle bajtów ile przeczytaliśmy. Pliki binarne będą zawierały w sobie znaki \0 co wcale nie oznacza, że kończą one sekwencję.
		*/
		Output.append(Buffer, BytesRead);
	}
	
	fclose(F);
	return Output;
}

proZPRd::File::Lines_t proZPRd::File::GetLines(const std::string & FileName)
{
	std::ifstream F(FileName);
	
	if(!F.good())
		throw Tools::Exception(EXCEPTION_PARAMS, "fstream() failed...");
	
	Lines_t Buffer;
	std::string Temp;
	
	while(std::getline(F, Temp))
		Buffer.push_back(Temp);
	
	/*
		Plik jest automatycznie zamykany przy usuwaniu strumienia, wiec F.close() jest zbedne
	*/
	
	return Buffer;
}

proZPRd::File::FileStruct proZPRd::File::SplitFileName(const std::string & FileName)
{
	struct FileStruct FN;
	std::size_t pos = FileName.find(".");
	if(pos == std::string::npos)
		throw Tools::Exception(EXCEPTION_PARAMS, "SplitFileName failed...");
	FN.Name = FileName.substr(0, pos);
	FN.Extension = FileName.substr(pos + 1);
	return FN;
} 