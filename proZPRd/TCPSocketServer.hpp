#pragma once

#include "Tools/NoCopyU.hpp"

#include <string>
#include <memory>

#include "TCPSocketClient.hpp"

namespace proZPRd
{
	class TCPSocketServer : public Tools::NoCopyU
	{
		private:
			static const unsigned int BackLogSize = 32;
			
		public:
			TCPSocketServer(const std::string & Ip, const unsigned short Port);
			~TCPSocketServer();
		private:
			const std::string Ip;
			const unsigned short Port;
		
		private:
			int Socket;
		
		public:
			typedef std::unique_ptr<TCPSocketClient> NewClientPtr_t;
			typedef std::function<void (NewClientPtr_t)> NewClient_f;
			void Main(NewClient_f AcceptFunction) const;
	};
}