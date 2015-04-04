#include "Exception.hpp"

proZPRd::Tools::Exception::Exception(const std::string & PrettyFunction, const std::string & File, const unsigned int Line, const std::string & Message): PrettyFunction(PrettyFunction), File(File), Line(Line), Message(Message)
{
	
}
proZPRd::Tools::Exception::~Exception()
{
	
}
const std::string proZPRd::Tools::Exception::ToString() const
{
	return PrettyFunction + "@" + File + ":" + std::to_string(Line) + " - " + Message;
}
const char * proZPRd::Tools::Exception::what() const noexcept
{
	return ToString().c_str();
}