#pragma once

#include "Tools/NoCopyU.hpp"

#include "HTTPRequestProcessor.hpp"
#include "TCPSocketServer.hpp"

#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

namespace proZPRd
{
	/**
		Klasa reprezentująca obiekt wątku roboczego obsługującego zapytania.
		
		Kiedy obiekt klasy jest tworzony - zostaje uruchomiony wątek, który oczekuje na nowe połączenia pojawiające się w kolejce.
		Obiekt zajmuje się obsługą jednego połączenia na raz, następnie je zamyka.
		Obiekt uruchamia nowy wątek samoczynnie, działa on tak długo, dopóki flaga ShouldExit nie jest ustawiona
	*/
	class ServerThread : public Tools::NoCopyU
	{
		public:
			/**
				Konstruktor.
				
				ThisThreadId - numer porządkowy wątku, służący wyłącznie do celów diagnostycznych
				ShouldExit - flaga informująca o tym, czy wątek powinien już zakończyć działanie
				HRP - obiekt dostarczający kontekst parsowania zapytań
				NewClientsQueue - kolejka w której umieszczane są przychodzące połączenia. Wątek pobiera połączenia z tej kolejki
				NewClientsQueueMutex - mutex służący do synchronizacji kolejki
				NewClientsNewData - zmienna warunkowa blokująca wątek do czasu pojawienia się nowych danych w kolejce
			*/
			ServerThread(const unsigned int ThisThreadId, const volatile bool * ShouldExit, const HTTPRequestProcessor & HRP, std::queue<TCPSocketServer::NewClientPtr_t> & NewClientsQueue, std::mutex & NewClientsQueueMutex, std::condition_variable & NewClientsNewData);
			
			/**
				Destruktor.
				
				Wykonuje join() na wątku.
				Konstruktor powinien być wołany PO ustawieniu flagi ShouldExit, inaczej może dojść do zakleszczenia.
			*/
			~ServerThread();
			
		private:
			const unsigned int ThisThreadId;
			const volatile bool * ShouldExit;
			const HTTPRequestProcessor & HRP;
			
			std::queue<TCPSocketServer::NewClientPtr_t> & NewClientsQueue;
			std::mutex & NewClientsQueueMutex;
			std::condition_variable & NewClientsNewData;
			
		private:
			/**
				Wątek roboczy
			*/
			std::thread MainThread;
			
			/**
				Metoda wykonywana przez wątek
			*/
			void Main();
	};
}