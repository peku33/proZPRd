#pragma once

#include "Tools/NoCopyU.hpp"

#include <unordered_map>
#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"

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
			
		public:
			/**
			*	Konstruktor
			*	@param HostMapping przyjmuje jako argument std::unordered_map opisującą mapping Host: -> Folder
			*/
			HTTPRequestProcessor(const HostMapping_t & HostMapping);
		
		private:
			const HostMapping_t & HostMapping;
		
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