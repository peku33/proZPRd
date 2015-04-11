#include "File.hpp"

bool proZPRd::File::Exists(const std::string & FileName)
{
	struct stat s;
	if(stat(FileName.c_str(), &s) == 0)
	{
		if(s.st_mode & S_IFDIR) 
			return false;
	}
	else 
		return false;
	
	return true;
}

std::string proZPRd::File::ToString(const std::string & FileName)
{
	std::ifstream file(FileName);
	std::string buffer;
	std::string line;
	
	if(!file.good()) throw Tools::Exception(EXCEPTION_PARAMS, "BLAD: Plik nie istnieje!");
		
	while(file)
	{
		std::getline(file, line);
		buffer += line;
		if(file)
			buffer += '\n';
	}
	
	return buffer;
}

