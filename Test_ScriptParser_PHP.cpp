#include <iostream>
#include "proZPRd/ScriptParser.hpp"
#include "proZPRd/Logger.hpp"

int main()
{
	std::cout <<
		"Program testujacy parsowanie skryptow PHP pod linuxem\n"
		"Program uruchomi skrypt o nazwie TestData/phpInfo.php i wyswietli jego zawartosc na ekran:\n"
	<< std::endl;
	
	try
	{
		proZPRd::ScriptParser PhpParser("/usr/bin/php");
		std::cout << PhpParser.Parse("TestData/phpInfo.php") << std::endl;
	}
	catch(const std::exception & E)
	{
		proZPRd::Logger::Error(E.what());
	}
	return 0;
}