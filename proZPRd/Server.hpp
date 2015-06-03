#pragma once

#include "Tools/NoCopyU.hpp"

#include <boost/asio/io_service.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ip/address.hpp>

#include "ServerThread.hpp"
#include <queue>
#include <mutex>
#include <condition_variable>

namespace proZPRd
{
	class Server : public Tools::NoCopyU
	{
		public:
			Server(const std::string & ListenAddressStr, const unsigned short ListenPort, const unsigned int ThreadsNum);
			
		private:
			const std::string & ListenAddressStr;
			const unsigned short ListenPort;
		
		public:
			void Run();
		
		/**
			Elementy sieciowe
		*/
		private:
			/**
				Zarządca głównej pętli przetwarzającej przychodzące dane
			*/
			boost::asio::io_service IS;
			
			/**
				Zestaw sygnałów kończących działanie programu
			*/
			boost::asio::signal_set SS;
			
			/**
				Akcaptor połączeń TCP
			*/
			boost::asio::ip::tcp::acceptor AC;
			
			/**
				Socket który przyjmie przychodzące połaczenie
			*/
			boost::asio::ip::tcp::socket NewClientSocket;
		
		private:
			void CreateAcceptor();
			void CreateQuitter();
		
		/**
			Obsługa wątków
		*/
		private:
			std::queue<boost::asio::ip::tcp::socket> SocketQueue;
			std::mutex SocketQueueMutex;
			std::condition_variable SocketQueueNotEmpty;
			
			volatile bool ShouldExit;
			std::vector<std::unique_ptr<ServerThread>> ServerThreads;
	};
}