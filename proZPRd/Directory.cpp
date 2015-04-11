#include "Directory.hpp"

#include <sys/stat.h>
#include <dirent.h>
#include "Tools/Exception.hpp"

bool proZPRd::Directory::Exists(const std::string & DirectoryName)
{
	struct stat S;
	return (stat(DirectoryName.c_str(), &S) == 0) && S_ISDIR(S.st_mode);
}

proZPRd::Directory::DirectoryEntries proZPRd::Directory::List(const std::string & DirectoryName)
{	
	DIR * D = opendir(DirectoryName.c_str());
	if(D == NULL) 
		throw Tools::Exception(EXCEPTION_PARAMS, "opendir() failed...");
	
	struct DirectoryEntries DE;
	struct dirent * Entry;
	
	while((Entry = readdir(D)) != NULL)
	{
		struct stat S;
		std::string FilePath = DirectoryName + GetDirectorySeparator() + std::string(Entry->d_name);
		if(stat(FilePath.c_str(), &S) != 0)
			continue; // Jeśli pliku nie udało się sprawdzić, pomijamy go
		
		if(S_ISDIR(S.st_mode))
			DE.Directories.insert(std::string(Entry->d_name));
		else if(S_ISREG(S.st_mode))
			DE.Files.insert(std::string(Entry->d_name));
	}
	
	closedir(D);
	return DE;
}
std::string proZPRd::Directory::GetDirectorySeparator()
{
	#if defined(WIN32) || defined(_WIN32) 
		return "\\";
	#else 
		return "/";
	#endif
}