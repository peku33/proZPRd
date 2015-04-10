#include "File.hpp"

bool proZPRd::File::Exists(const std::string & FileName)
{
	struct stat s;
	if(stat(FileName.c_str(), &s) == 0)
	{
		if(s.st_mode & S_IFDIR) return false;
	}else return false;
	
	return true;
}

std::string proZPRd::File::ToString(const std::string & FileName)
{
	std::ifstream t(FileName);
	std::string str;
	
	if(!t.good()) throw Tools::Exception(EXCEPTION_PARAMS, "BLAD: Plik nie istnieje!");
		
	t.seekg(0, std::ios::end);   
	str.reserve(t.tellg());
	t.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
	
	return str;
}

