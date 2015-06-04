#include "ScriptParser.hpp"

proZPRd::ScriptParser::ScriptParser(const std::string & ParserExecutable): ParserExecutable(ParserExecutable)
{
	
}
std::string proZPRd::ScriptParser::Parse(const std::string & ScriptName)
{
	//1. Sprawdź, czy ParserExecutable istnieje. Nie -> wyjątek
	
	//2. Uruchamiasz proces parsera, przekierowujesz jego wyjście na swoje wejście.
	//Jakiś względnie sprawny, ACZKOLWIEK NIE DO SKOPIOWANIA pomysł jest tu: http://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c
	
	//3. Sprawdzasz kod wyjścia programu -> zły -> wyjątek
	
	//4. Jeśli ok - zwracasz to, co zwrócił program
	
	return std::string();
}