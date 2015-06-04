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
	class Server : public Tools::NoCopyU
	{
		public:
			Server(const std::string & ListenAddressStr, const unsigned short ListenPort, const unsigned int ThreadsNum, const HTTPRequestProcessor & HRP);
			~Server();
			
		private:
			const HTTPRequestProcessor & HRP;
		
		public:
			void Run();
		
		private:
			static void SignalHandler(int Signal);
			
		private:
			const TCPSocketServer TSS;
			void OnNewClient(TCPSocketServer::NewClientPtr_t NewClient);
		
		/**
			Wątki
		*/
		private:
			std::queue<TCPSocketServer::NewClientPtr_t> NewClientsQueue;
			std::mutex NewClientsQueueMutex;
			std::condition_variable NewClientsNewData;
			
			volatile bool ShouldExit;
			std::vector<std::unique_ptr<ServerThread>> Threads;
	};
}