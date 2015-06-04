#pragma once

#include "Tools/NoCopyU.hpp"

#if defined(_WIN32)
	#include <winsock2.h>
#else
	#include <unistd.h>
	#include <arpa/inet.h>
#endif

#include <string>

namespace proZPRd
{
	/**
	*	@file
	*	@version 1.0
	*	@class TCPSocketClient
	*	Klasa opisująca gniazdo komunikacyjne serwer-klient
	*/
	class TCPSocketClient : public Tools::NoCopyU
	{
		public:
			/**
			*	Konstruktor.
			*	
			*	@param Socket - deskryptor gniazda otrzymany z TCPSocketServer
			*	@param RemoteAddress - adres klienta
			*/
			TCPSocketClient(const int Socket, const struct sockaddr_in & RemoteAddress);
			
			/**
			*	Destruktor.
			*
			*	Zamyka gniazdo
			*/
			~TCPSocketClient();
			
		private:
			const int Socket;
			const struct sockaddr_in RemoteAddress;
		
		public:
			/**
			*	Odbiera dane od klienta
			*	
			*	@param Output - wskaźnik na bufor który odbierze dane
			*	@param MaxLength - maksymalna ilość danych wpisana na raz do bufora
			*	
			*	@return Zwraca długość odebranych danych
			*/
			size_t Read(char * Output, const size_t MaxLength);
			
			/**
			*	Wysyła dane do klienta
			*	
			*	@param Input - wskaźnik na bufor zawierający dane do wysłania
			*	@param Length - Długość danych do wysłania
			*/
			void Write(const char * Input, const size_t Length);
			
			/**
			*	@return Zwraca adres klienta w postaci adres IP z kropkami
			*/
			std::string GetRemoteIpStr() const;
			
			/**
			*	@return Zwraca port klienta
			*/
			unsigned short GetRemotePort() const;
			
			/**
			*	@return Zwraca adres + : + port klienta
			*/
			std::string GetRemoteIpPortStr() const;
	};
}