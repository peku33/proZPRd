#include "IniParser.hpp"
#include "Tools/Exception.hpp"
#include "Strings.hpp"

proZPRd::IniParser::IniParser(const std::string & Input)
{
	
	auto Lines = Strings::SplitString(Input, "\n");
	int SizeOfLines = Lines.size() - 1;
	std::string LineParts;
	Threads = 0;
	Port = 0;
	while(SizeOfLines >= 0)
	{
		LineParts = Strings::SplitString(Lines[SizeOfLines], "=");
		
		if((LineParts[0] == "directory") && (LineParts.size() == 3))
		{
			Dir.insert(std::pair<std::string, std::string>(LineParts[1], LineParts[2]));
		}
		else if((LineParts[0] == "errorlog") && (LineParts.size() == 2))
		{
			Errorlog = LineParts[1];
		}
		else if((LineParts[0] == "port") && (LineParts.size() == 2))
		{
			Port = std::stoi(LineParts[1]);
		}
		else if((LineParts[0] == "threads") && (LineParts.size() == 2))
		{
			Threads = std::stoi(LineParts[1]);
		}
		else if((LineParts[0] == "addparser") && (LineParts.size() == 2))
		{
			AdditionalParsers.insert(LineParts[1]);
		}
		else if((LineParts[0] == "#" || LineParts[0] == "\n"))
		{
			continue;
		}
		else
		{
			throw Tools::Exception(EXCEPTION_PARAMS, "Ini parser syntax error");
		}
		--SizeOfLines;
	}
	
	if(Dir.size() == 0 || Port == 0 || Threads == 0 || Errorlog.size() == 0)
	{
		throw Tools::Exception(EXCEPTION_PARAMS, "Ini parser syntax error: some parameters are missing. Please provide them.");
	}
		
} 