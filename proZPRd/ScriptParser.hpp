#pragma once

#include <string>

namespace proZPRd
{
	/**
	*	@file
	*	@version 1.0
	*	@class ScriptParser
	*	@brief Klasa odpowiadająca za uruchamianie parserów.
	*
	*/
	class ScriptParser
	{
		public:
			/**
			*	Konstruktor
			*
			*	@param ParserExecutable - ścieżka do aplikacji (np .exe na windows) parsera
			*/
			ScriptParser(const std::string & ParserExecutable);
			
		private:
			const std::string ParserExecutable;
		
		public:
			/**
			*	Metoda która uruchomi podany parser i wykona podany jako ScriptName skrypt.
			*	@return Zwraca wartość którą parser zwróci na wyjściu w postaci std::string.
			*/
			std::string Parse(const std::string & ScriptName) const;
	};
}