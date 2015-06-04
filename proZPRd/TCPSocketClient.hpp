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
	class TCPSocketClient : public Tools::NoCopyU
	{
		public:
			TCPSocketClient(const int Socket, const struct sockaddr_in & RemoteAddress);
			~TCPSocketClient();
			
		private:
			const int Socket;
			const struct sockaddr_in RemoteAddress;
		
		public:
			size_t Read(char * Output, const size_t MaxLength);
			void Write(const char * Input, const size_t Length);
			
			std::string GetRemoteIpStr() const;
			unsigned short GetRemotePort() const;
			std::string GetRemoteIpPortStr() const;
	};
}