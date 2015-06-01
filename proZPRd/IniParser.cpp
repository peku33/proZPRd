#include "IniParser.hpp"
#include "Tools/Exception.hpp"


proZPRd::IniParser::IniParser(const std::string & Input)
{
	
	if(Input.find("directory", 0) == std::string::npos)
		throw Tools::Exception(EXCEPTION_PARAMS, "Ini parser syntax error: directory settings not found");
	
	unsigned DirEnd;
	if((DirEnd = Input.find("\n", 11)) == std::string::npos)
		throw Tools::Exception(EXCEPTION_PARAMS, "Ini parser syntax error: directory settings not found");
	Dir = Input.substr(10, DirEnd - 10);
	
	unsigned ErrorlogPos;
	if((ErrorlogPos=Input.find("errorlog", 0)) == std::string::npos)
		throw Tools::Exception(EXCEPTION_PARAMS, "Ini parser syntax error: errorlog settings not found");
	
	unsigned ErrorlogEnd;
	if((ErrorlogEnd = Input.find("\n", ErrorlogPos + 9)) == std::string::npos)
		throw Tools::Exception(EXCEPTION_PARAMS, "Ini parser syntax error: errorlog settings not found");
	Errorlog = Input.substr(ErrorlogPos + 9,ErrorlogEnd  -  ErrorlogPos - 9);
	
	unsigned PortPos;
	if((PortPos=Input.find("port", 0)) == std::string::npos)
		throw Tools::Exception(EXCEPTION_PARAMS, "Ini parser syntax error: port settings not found");
	
	unsigned PortEnd;
	if((PortEnd = Input.find("\n", PortPos + 5)) == std::string::npos)
		throw Tools::Exception(EXCEPTION_PARAMS, "Ini parser syntax error: port settings not found");
	Port = std::stoi(Input.substr(PortPos + 4,PortEnd  -  PortPos - 4));
	
	unsigned ThreadsPos;
	if((ThreadsPos=Input.find("threads", 0)) == std::string::npos)
		throw Tools::Exception(EXCEPTION_PARAMS, "Ini parser syntax error: threads settings not found");
	
	unsigned ThreadsEnd;
	if((ThreadsEnd = Input.find("\n", ThreadsPos + 7)) == std::string::npos)
		throw Tools::Exception(EXCEPTION_PARAMS, "Ini parser syntax error: threads settings not found");
	Threads = std::stoi(Input.substr(ThreadsPos + 7,ThreadsEnd  -  ThreadsPos - 7));
	
	unsigned ParserPos;
	unsigned ParserEnd;
	while((ParserPos=Input.find("addparser", 0)) != std::string::npos)
	{
		if((ParserEnd = Input.find("\n", ParserPos +10)) == std::string::npos)
			throw Tools::Exception(EXCEPTION_PARAMS, "Ini parser syntax error: additional parser settings not found");
		AdditionalParsers.insert(Input.substr(ParserPos + 9,ParserEnd  -  ParserPos - 9));
	}
	
} 