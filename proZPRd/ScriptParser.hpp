#pragma once

#include <string>

namespace proZPRd
{
	class ScriptParser
	{
		public:
			/**
			*	Konstruktor
			*
			*	ParserExecutable - ścieżka do aplikacji (np .exe na windows) parsera
			*/
			ScriptParser(const std::string & ParserExecutable);
			
		private:
			const std::string ParserExecutable;
		
		public:
			/**
			*	Metoda która uruchomi podany parser i wykona podany jako ScriptName skrypt
			*	Zwraca wartość którą parser zwróci na wyjściu
			*/
			std::string Parse(const std::string & ScriptName) const;
	};
}