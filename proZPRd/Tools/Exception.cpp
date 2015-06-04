#include "Exception.hpp"

#include <iostream>

proZPRd::Tools::Exception::Exception(const std::string & PrettyFunction, const std::string & FileName, const unsigned int Line, const std::string & Message)
{
	AsString = PrettyFunction + "@" + FileName + ":" + std::to_string(Line) + " - " + Message;
}
proZPRd::Tools::Exception::~Exception()
{
	
}
const std::string proZPRd::Tools::Exception::ToString() const
{
	return AsString;
}
const char * proZPRd::Tools::Exception::what() const noexcept
{
	return AsString.c_str();
}