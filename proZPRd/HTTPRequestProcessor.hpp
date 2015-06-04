#pragma once

#include "Tools/NoCopyU.hpp"

#include <unordered_map>
#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"
#include <boost/regex.hpp>
#include "ScriptParser.hpp"

namespace proZPRd
{
	/**
	*	@file
	*	@version 1.0
	*	@class HTTPRequestProcessor
	*	@brief Klasa służąca do przetwarzania zapytania na odpowiedź.
	*
	*	Zajmuje się dopasowaniem ustawień i zmiennych zapytania i wytworzeniem odpowiedzi
	*/
	class HTTPRequestProcessor : public Tools::NoCopyU
	{
		public:
			/**
			*	Typ mapy opisującej mapping Host: -> Folder
			*/
			typedef std::unordered_map<std::string, std::string> HostMapping_t;
			
			/**
			*	Typ mapy opisującej mapping Regex -> Ścieżka parsera
			*/
			typedef std::unordered_map<std::string, std::string> ParserMapping_t;
			
		public:
			/**
			*	Konstruktor
			*	@param HostMapping przyjmuje jako argument std::unordered_map opisującą mapping Host: -> Folder
			*/
			HTTPRequestProcessor(const HostMapping_t & HostMapping, const ParserMapping_t & PM);
		
		private:
			const HostMapping_t HostMapping;
			
			/**
			*	Wektor na podstawie którego będziemy dopasowywać.
			*	Każdy element zawiera parę:
			*		.first => skompilowany regex czekający na porównanie
			*		.second => parser obsługujący zapytanie
			*/
			std::vector<std::pair<boost::regex, ScriptParser>> RunningRegexes;
		public:
			/**
			*	Metoda która wytworzy odpowiedź na podstawie zapytania
			*	@param HR Przyjmuje jako parametr HTTPRequest.
			*/
			HTTPResponse::HTTPResponsePtr Process(const HTTPRequest & HR) const;
		
		private:
			/**
			*	Sprawdza, czy podany URL nie zawiera nieprawidłowych znaków
			*	@return Zwraca true jeśli poprawny, false jeśli nie.
			*/
			static bool IsURLValid(const std::string & URL);
	};
}