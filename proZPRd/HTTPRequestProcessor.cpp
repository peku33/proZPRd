#include "HTTPRequestProcessor.hpp"

#include <stdexcept>
#include "HTTPResponseCode.hpp"
#include "HTTPResponseNotModified.hpp"
#include "HTTPResponseContent.hpp"
#include "File.hpp"

#include <ctype.h>
#include <iostream>

proZPRd::HTTPRequestProcessor::HTTPRequestProcessor(const HostMapping_t & HostMapping): HostMapping(HostMapping)
{
	
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
	
	/**
		Plik istnieje, sprawdzamy ETag
	*/
	std::string RequestETag = HR.GetRequestedETag();
	std::string FileETag = File::GetETag(FilePath);
	if(!RequestETag.empty())
		if(RequestETag == FileETag)
			return HTTPResponse::HTTPResponsePtr(new HTTPResponseNotModified());
	
	File::FileStruct FilePathStruct = File::SplitFileName(FilePath);
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