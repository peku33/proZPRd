#pragma once

#include <string>
#include "HTTPRequestProcessor.hpp"

namespace proZPRd
{
	/**
	*	@file
	*	@version 1.0
	*	@class Config
	*	@brief Klasa reprezentująca plik konfiguracyjny
	*/
	class Config
	{
		public:
		/**
		*	Konstrukor 
		*	@param FileName - nazwa pliku konfiguracyjnego.
		*/
			Config(const std::string & FileName);
		
		private:
			const std::string FileName;
		
		private:
			unsigned int ThreadsNum;
			std::string BindAddress;
			unsigned int BindPort;
			HTTPRequestProcessor::HostMapping_t HostMapping;
			HTTPRequestProcessor::ParserMapping_t ParserMapping;
		
		public:
			/**
			*	@return Zwraca liczbe wątków.
			*/
			unsigned int GetThreadsNum() const;
			/**
			*	@return Zwraca adres IP na którym pracuje serwer.
			*/
			std::string GetBindAddress() const;
			/**
			*	@return Zwraca port.
			*/
			unsigned int GetBindPort() const;
			/**
			*	@return Zwraca mapping hostów -> katalog lokalny.
			*/
			HTTPRequestProcessor::HostMapping_t GetHostMapping() const;
			/**
			*	@return Zwraca zdefiniowane parsery.
			*/
			HTTPRequestProcessor::ParserMapping_t GetParserMapping() const;
	};
}