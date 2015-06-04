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
	*	Klasa opisująca gniazdo komunikacyjne serwer-klient
	*/
	class TCPSocketClient : public Tools::NoCopyU
	{
		public:
			/**
			*	Konstruktor.
			*	
			*	Socket - deskryptor gniazda otrzymany z TCPSocketServer
			*	RemoteAddress - adres klienta
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
			*	Output - wskaźnik na bufor który odbierze dane
			*	MaxLength - maksymalna ilość danych wpisana na raz do bufora
			*	
			*	Zwraca długość odebranych danych
			*/
			size_t Read(char * Output, const size_t MaxLength);
			
			/**
			*	Wysyła dane do klienta
			*	
			*	Input - wskaźnik na bufor zawierający dane do wysłania
			*	Length - Długość danych do wysłania
			*/
			void Write(const char * Input, const size_t Length);
			
			/**
			*	Zwraca adres klienta w postaci adres IP z kropkami
			*/
			std::string GetRemoteIpStr() const;
			
			/**
			*	Zwraca port klienta
			*/
			unsigned short GetRemotePort() const;
			
			/**
			*	Zwraca adres + : + port klienta
			*/
			std::string GetRemoteIpPortStr() const;
	};
}