#include "Exception.hpp"

proZPRd::Tools::Exception::Exception(const std::string & PrettyFunction, const std::string & FileName, const unsigned int Line, const std::string & Message): PrettyFunction(PrettyFunction), FileName(FileName), Line(Line), Message(Message)
{
	
}
proZPRd::Tools::Exception::~Exception()
{
	
}
const std::string proZPRd::Tools::Exception::ToString() const
{
	return PrettyFunction + "@" + FileName + ":" + std::to_string(Line) + " - " + Message;
}
const char * proZPRd::Tools::Exception::what() const noexcept
{
	return ToString().c_str();
}