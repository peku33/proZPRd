#include "HTTPRequestProcessor.hpp"

#include <stdexcept>
#include "HTTPResponseCode.hpp"
#include "HTTPResponseNotModified.hpp"
#include "HTTPResponseContent.hpp"
#include "File.hpp"

#include <ctype.h>

proZPRd::HTTPRequestProcessor::HTTPRequestProcessor(const HostMapping_t & HostMapping, const ParserMapping_t & PM): HostMapping(HostMapping)
{
	/**
		Kompilacja wyrażeń regularnych
	*/
	for(auto & Parser : PM)
	{
		boost::regex R(Parser.first);
		RunningRegexes.push_back(std::make_pair(R, ScriptParser(Parser.second)));
	}
}
proZPRd::HTTPResponse::HTTPResponsePtr proZPRd::HTTPRequestProcessor::Process(const HTTPRequest & HR) const
{
	/**
		Sprawdzamy, czy ten host jest obsługiwany
	*/
	std::string RootDirectory;
	try
	{
		RootDirectory = HostMapping.at(HR.GetHost());
	}
	catch(std::out_of_range &)
	{
		return HTTPResponse::HTTPResponsePtr(new HTTPResponseCode(403));
	}
	
	/**
		Sprawdzamy, czy ścieżka zawiera niedozwolone znaki
	*/
	const std::string URL = HR.GetURL();
	if(!IsURLValid(URL))
		return HTTPResponse::HTTPResponsePtr(new HTTPResponseCode(500));
	
	/**
		Poprawiamy ukośniki i sprawdzamy, czy plik istnieje
	*/
	const std::string FilePath = File::FixSlashes(RootDirectory + URL);
	if(!File::Exists(FilePath))
		return HTTPResponse::HTTPResponsePtr(new HTTPResponseCode(404));
	File::FileStruct FilePathStruct = File::SplitFileName(FilePath);
		
	/**
		Plik istnieje, sprawdzamy parsowanie
	*/
	for(auto & Parser : RunningRegexes)
	{
		if(boost::regex_match(FilePath, Parser.first))
		{
			std::string ParserResult = Parser.second.Parse(FilePath);
			return HTTPResponse::HTTPResponsePtr(new HTTPResponseContent(ParserResult, HTTPResponseContent::GetContentTypeByExtension("html"), std::string()));
		}
	}
	
	/**
		Plik istnieje, sprawdzamy ETag
	*/
	std::string RequestETag = HR.GetRequestedETag();
	std::string FileETag = File::GetETag(FilePath);
	if(!RequestETag.empty())
		if(RequestETag == FileETag)
			return HTTPResponse::HTTPResponsePtr(new HTTPResponseNotModified());
	
	std::string FileContent = File::ToString(FilePath);
	return HTTPResponse::HTTPResponsePtr(new HTTPResponseContent(FileContent, HTTPResponseContent::GetContentTypeByExtension(FilePathStruct.Extension), FileETag));
}
bool proZPRd::HTTPRequestProcessor::IsURLValid(const std::string & URL)
{
	for(auto C : URL)
		if(!isgraph(C))
			return false;
	
	if(URL.find("..") != std::string::npos)
		return false;
		
	return true;
}