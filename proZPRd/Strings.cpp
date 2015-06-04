#include "Strings.hpp"

#include <algorithm>

proZPRd::Strings::StringParts_t proZPRd::Strings::SplitString(const std::string & String, const std::string & Delimiter)
{
	StringParts_t StringParts;
	size_t LastLineEndPosition = 0;
	size_t ThisLineEndPosition = 0;
	
	while(true)
	{
		// Znajdź koniec obecnej linii
		ThisLineEndPosition = String.find(Delimiter, LastLineEndPosition);
		
		// Wytnij tekst od tego poprzedniego końca do końca
		StringParts.push_back(String.substr(LastLineEndPosition, ThisLineEndPosition - LastLineEndPosition));
		
		// Jeśli nie ma nic więcej, to koniec pętli
		if(ThisLineEndPosition == std::string::npos)
			break;
		
		// W następnym obiegu zaczynamy od ostatniej pozycji + długość delimitera
		LastLineEndPosition = ThisLineEndPosition + Delimiter.length();
	}
	
	return StringParts;
}

std::string proZPRd::Strings::Trim(const std::string & String)
{
	auto First = std::find_if(String.begin(), String.end(), isgraph);
	auto Last = std::find_if(String.rbegin(), String.rend(), isgraph);
	
	return std::string(First, Last.base());
}