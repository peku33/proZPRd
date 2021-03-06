#pragma once

#include "Tools/NoCopyU.hpp"

#include <string>
#include <memory>

#include "TCPSocketClient.hpp"

namespace proZPRd
{
	/**
	*	@file
	*	@version 1.0
	*	@class TCPSocketServer
	*	@brief Klasa opisująca gniazdo nasłuchujące na połączenia
	*
	*	Klasa posiada metodę Main() która będzie wołała podaną w parametrze funkcję wraz z każdym nowym połączeniem.
	*/
	class TCPSocketServer : public Tools::NoCopyU
	{
		private:
			/**
			*	Maksymalna długość kolejki oczekujących na akceptację połączeń
			*/
			static const unsigned int BackLogSize = 32;
			
		public:
			/**
			*	Konstruktor
			*	
			*	@param Ip - adres IP do nasłuchiwania w postaci z kropkami
			*	@param Port - port do nasłuchiwania
			*/
			TCPSocketServer(const std::string & Ip, const unsigned short Port);
			
			/**
			*	Destruktor.
			*	
			*	Zamyka gniazdo
			*/
			~TCPSocketServer();
			
		private:
			const std::string Ip;
			const unsigned short Port;
		
		private:
			int Socket;
		
		public:
			/**
			*	Typ definiujący parametr przekazywany do funkcji obsługującej nowych klientów
			*/
			
			typedef std::unique_ptr<TCPSocketClient> NewClientPtr_t;
			
			/**
			*	Typ definiujący funkcję obsługującą połączenia
			*/
			typedef std::function<void (NewClientPtr_t)> NewClient_f;
		
			/**
			*	Metoda która uruchomi główną pętlę oczekującą na połączenia
			*	@param AcceptFunction przyjmuje jako argument std::function - fukncję obsługującą połączenia.
			*/
			void Main(NewClient_f AcceptFunction) const;
	};
}