#pragma once

#include <string>
#include <set>
#include <map>
namespace proZPRd
{
	/**
	*	@file
	*	@version 1.0
	*	@class IniParser
	*	@brief Klasa parsująca plik konfiguracyjny ini. 
	*	
	*	Budowa pliku konfiguracyjnego:
	*	directory host katalog_na_dysku
	*	directory host2 katalog_na_dysku2
	*	...
	*	errorlog plik_z_logami
	*	port port_serwera
	*	threads liczba_watkow
	*	addparser nazwa_parsera	
	*/
	class IniParser
	{		
		private:
			std::map<std::string, std::string> Dir;
			std::string Errorlog;
			int Port;
			int Threads;
			std::set<std::string> AdditionalParsers;
		
		public:
		
			/**
			*	Konstruktor klasy IniParser.
			*	@param Input Zawartość pliku konfiguracyjnego .ini w postaci std::string
			*/
			IniParser(const std::string & Input);
			
			/**
			*	@return Zwraca mapping host -> katalog.
			*/
			std::map<std::string, std::string> GetDir() {return Dir;};
			
			/**
			*	@return Zwraca ścieżkę do pliku z logami.
			*/
			std::string GetErrorlog() {return  Errorlog;};
			
			/**
			*	@return Zwraca port na którym pracuje serwer.
			*/
			int GetPort() {return Port;};
			
			/**
			*	@return Zwraca liczbę wątków.
			*/
			int GetThreads() {return Threads;};
			
			/**
			*	@return Zwraca liczbę dodatkowe parsery w postaci std::set.
			*/
			std::set<std::string> GetAdditionalParsers() {return AdditionalParsers;};
	};
}
