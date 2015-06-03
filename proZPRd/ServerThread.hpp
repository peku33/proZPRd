#pragma once

#include "Tools/NoCopyU.hpp"

#include <queue>
#include <boost/asio/ip/tcp.hpp>
#include <mutex>
#include <condition_variable>
#include <thread>

namespace proZPRd
{
	class ServerThread : public Tools::NoCopyU
	{
		public:
			ServerThread(const unsigned int ThisThreadId, const volatile bool * ShouldExit, std::queue<boost::asio::ip::tcp::socket> & SocketQueue, std::mutex & SocketQueueMutex, std::condition_variable & SocketQueueNotEmpty);
			~ServerThread();
			
		private:
			const unsigned int ThisThreadId;
			const volatile bool * ShouldExit;
			
			std::queue<boost::asio::ip::tcp::socket> & SocketQueue;
			std::mutex & SocketQueueMutex;
			std::condition_variable & SocketQueueNotEmpty;
			
		private:
			std::thread MainThread;
			void Main();
	};
}