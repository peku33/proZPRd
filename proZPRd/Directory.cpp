#include "Directory.hpp"

bool proZPRd::Directory::Exists(const std::string & DirectoryName)
{
	struct stat s;
	return ((s.st_mode & S_IFDIR) && (stat(DirectoryName.c_str(), &s) == 0));
}

proZPRd::Directory::DirectoryEntries proZPRd::Directory::List(const std::string & DirectoryName)
{
	struct DirectoryEntries dE;
	struct dirent *entry;
	
	DIR * dir = opendir(DirectoryName);
	if(!dir) 
		throw Tools::Exception(EXCEPTION_PARAMS, "opendir() failed...");
		
	while((entry = readdir(dir)) != NULL)
	{
		if(entry->d_type == DT_DIR)
			dE.Directories.insert(entry->d_name);
		else if (entry->d_type == DT_REG)
			dE.Files.insert(entry->d_name);
	}
	close(dir);
	
	return dE;
}

