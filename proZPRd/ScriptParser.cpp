#include "ScriptParser.hpp"
#include "File.hpp"
#include "Tools/Exception.hpp"

#ifdef _WIN32
  #define popen _popen
  #define pclose _pclose
#endif

proZPRd::ScriptParser::ScriptParser(const std::string & ParserExecutable): ParserExecutable(ParserExecutable)
{
	
}
std::string proZPRd::ScriptParser::Parse(const std::string & ScriptName)
{
	if(!proZPRd::File::Exists(ScriptName))
		throw Tools::Exception(EXCEPTION_PARAMS, "file: " + ScriptName + " not found!");
	
	FILE* ParserProcess = popen(ScriptName.c_str(), "r");
    if (!ParserProcess)
		throw Tools::Exception(EXCEPTION_PARAMS, "popen() failed!");
	
    char Buffer[128];
    std::string Result;
	
    while(!feof(ParserProcess)) 
	{
    	auto Length = fread(Buffer, 1, sizeof(Buffer), ParserProcess);
		if(Length > 0)
			Result.append(Buffer, Length);
    }
	
    if(pclose(ParserProcess) != 0)
		throw Tools::Exception(EXCEPTION_PARAMS, ScriptName + " process returned an error!");
	
	return Result;
}