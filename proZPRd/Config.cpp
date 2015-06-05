#include "Config.hpp"

#include "File.hpp"
#include "Directory.hpp"
#include "Strings.hpp"

#include "Tools/Exception.hpp"

proZPRd::Config::Config(const std::string & FileName): FileName(FileName),
	ThreadsNum(0), BindAddress(), BindPort(80), HostMapping(), ParserMapping()
{
	File::Lines_t Lines = File::GetLines(FileName);
	for(std::string & LineRaw : Lines)
	{
		std::string Line = Strings::Trim(LineRaw);
		if(Line.length() == 0)
			continue;
		
		if(Line[0] == '#')
			continue;
		
		Strings::StringParts_t LineParts = Strings::SplitString(Line, " ");
		
		if(LineParts[0] == "ThreadsNum")
		{
			if(LineParts.size() == 2)
				ThreadsNum = stoi(LineParts[1]);
			else
				throw Tools::Exception(EXCEPTION_PARAMS, "Invalid ThreadsNum syntax");
		}
		else if(LineParts[0] == "BindAddress")
		{
			if(LineParts.size() == 2)
				BindAddress = LineParts[1];
			else
				throw Tools::Exception(EXCEPTION_PARAMS, "Invalid BindAddress syntax");
		}
		else if(LineParts[0] == "BindPort")
		{
			if(LineParts.size() == 2)
				BindPort = stoi(LineParts[1]);
			else
				throw Tools::Exception(EXCEPTION_PARAMS, "Invalid BindPort syntax");
		}
		else if(LineParts[0] == "VirtualHost")
		{
			if(LineParts.size() == 3)
			{
				if(!Directory::Exists(LineParts[2]))
					throw Tools::Exception(EXCEPTION_PARAMS, "Directory `" + LineParts[2] + "` for VHost `" + LineParts[1] + "` does not exist");
				
				if(!HostMapping.insert(std::make_pair(LineParts[1], LineParts[2])).second)
					throw Tools::Exception(EXCEPTION_PARAMS, "Duplicated entry for VHost `" + LineParts[1] + "`");
			}
			else
				throw Tools::Exception(EXCEPTION_PARAMS, "Invalid VirtualHost syntax");
		}
		else if(LineParts[0] == "AddParser")
		{
			if(LineParts.size() == 3)
			{
				if(!ParserMapping.insert(std::make_pair(LineParts[1], LineParts[2])).second)
					throw Tools::Exception(EXCEPTION_PARAMS, "Duplicated entry for RegEx: `" + LineParts[1] + "`");
			}
			else
				throw Tools::Exception(EXCEPTION_PARAMS, "Invalid AddParser syntax");
		}
		else
			throw Tools::Exception(EXCEPTION_PARAMS, "Invalid command: `" + LineParts[0] + "`");
	}
}

unsigned int proZPRd::Config::GetThreadsNum() const
{
	return ThreadsNum;
}
std::string proZPRd::Config::GetBindAddress() const
{
	return BindAddress;
}
unsigned int proZPRd::Config::GetBindPort() const
{
	return BindPort;
}
proZPRd::HTTPRequestProcessor::HostMapping_t proZPRd::Config::GetHostMapping() const
{
	return HostMapping;
}
proZPRd::HTTPRequestProcessor::ParserMapping_t proZPRd::Config::GetParserMapping() const
{
	return ParserMapping;
}