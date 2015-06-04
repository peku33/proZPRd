#pragma once

#include "Tools/NoCopyU.hpp"

#include <string>
#include "HTTPRequestProcessor.hpp"

#include "TCPSocketServer.hpp"

#include <queue>
#include <mutex>
#include <condition_variable>

#include <vector>
#include <memory>
#include "ServerThread.hpp"

namespace proZPRd
{
	/**
	*	Klasa właściwego serwera HTTP
	*/
	class Server : public Tools::NoCopyU
	{
		public:
			/**
			*	Konstruktor.
			*
			*	ListenAddressStr - adres w postaci std::string pod którym serwer będzie nasłuchiwał
			*	ListenPort - port na którym serwer będzie nasłuchiwał
			*	ThreadsNum - ilość wątków roboczych które uruchomi Server
			*	HRP - referencja do procesora zapytań, który zosanie przekazany wątkom
			*
			*/
			Server(const std::string & ListenAddressStr, const unsigned short ListenPort, const unsigned int ThreadsNum, const HTTPRequestProcessor & HRP);
			
			/**
			*	Destruktor.
			*
			*	Zakończy swoje działanie dopiero wtedy, kiedy wszystkie wątki zostaną zatrzymane
			*/
			~Server();
			
		private:
			const HTTPRequestProcessor & HRP;
		
		public:
			/**
			*	Metoda uruchamiająca główną pętlę programu.
			*/
			void Run();
		
		private:
			/**
			*	Metoda która zajmie się obsłużeniem sygnału zakończenia programu
			*/
			static void SignalHandler(int Signal);
			
		private:
			/**
			*	Główne gniazdo nasłuchujące na nowe połączenia
			*/
			const TCPSocketServer TSS;
			
			/**
			*	Metoda która zostanie wywołana po podłączeniu się nowego klienta
			*/
			void OnNewClient(TCPSocketServer::NewClientPtr_t NewClient);
		
		/**
			Wątki
		*/
		private:
			/**
			*	Kolejka z której będą pobierać wątki robocze
			*/
			std::queue<TCPSocketServer::NewClientPtr_t> NewClientsQueue;
			
			/**
			*	Mutex kolejki
			*/
			std::mutex NewClientsQueueMutex;
			
			/**
			*	Zmienna warunkowa pod którą będziemy wysyłać powiadomienia odblokowujące nowe połączenia
			*/
			std::condition_variable NewClientsNewData;
			
			/**
			*	Zmienna przekazywana w postaci wskaźnika do wątków informująca o konieczności zakończenia
			*/
			volatile bool ShouldExit;
			
			/**
			*	Wektor przechowujący wątki
			*/
			std::vector<std::unique_ptr<ServerThread>> Threads;
	};
}