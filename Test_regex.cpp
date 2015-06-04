#include <iostream>
#include <regex>

int main()
{
	std::regex R(".*\\.php$");
	std::string Test("alamakota.php");
	
	std::cout << (std::regex_match(Test, R) ? "Y" : "N") << std::endl;
	return 0;
}