#include "Logger.hpp"

#include <iostream>
#include <iomanip>

#include <time.h>

void proZPRd::Logger::Ok(const std::string & Message)
{
	Display(Message, MessageType::OK);
}
void proZPRd::Logger::Info(const std::string & Message)
{
	Display(Message, MessageType::INFO);
}
void proZPRd::Logger::Warning(const std::string & Message)
{
	Display(Message, MessageType::WARNING);
}
void proZPRd::Logger::Error(const std::string & Message)
{
	Display(Message, MessageType::ERROR);
}
void proZPRd::Logger::Display(const std::string & Message, const MessageType MT)
{
	/*
		Otaczamy całą tą funkcję mutexem ponieważ
			- nie możemy dopuścić do przeplatania się wiadomości
			- równoległego wykonywania funkcji z biblioteki time.h
			- operacje nie są zbyt złożone aby szukać bardziej wyrafinowanych metod
	*/
	static std::mutex DisplayMutex;
	std::unique_lock<std::mutex> DisplayLock(DisplayMutex);
	
	/*
		Pobierz aktualny czas systemu
		Przekonwertuj go do postaci daty
	*/
	time_t Now = time(NULL);
	struct tm * NowDate = localtime(&Now);
	char TimeBuffer[64];
	strftime(TimeBuffer, sizeof(TimeBuffer), "%d-%m-%Y %H:%M:%S", NowDate);
	
	std::cout << "[" << std::setw(8) << MessageTypeToString(MT) << "] [" << TimeBuffer << "] " << Message << std::endl;
}
std::string proZPRd::Logger::MessageTypeToString(const MessageType MT)
{
	if(MT == MessageType::OK)
		return "Ok";
	else if(MT == MessageType::INFO)
		return "Info";
	else if(MT == MessageType::WARNING)
		return "Warning";
	else
		return "Error";
}