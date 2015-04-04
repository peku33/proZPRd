#include "Exception.hpp"

proZPRd::Tools::Exception(const std::string & PrettyFunction, const std::string & File, const unsigned int Line, const std::string & Message): PrettyFunction(PrettyFunction), File(File), Line(Line), Message(Message)
{
	
}
proZPRd::Tools::~Exception()
{
	
}
const proZPRd::Tools::std::string ToString() const
{
	return PrettyFunction + "@" + File + ":" + std::to_string(Line) + " - " + Message;
}
const char * proZPRd::Tools::what() const noexcept
{
	return ToString().c_str();
}