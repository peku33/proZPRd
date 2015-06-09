#include "TCPSocketServer.hpp"

#if defined(_WIN32)
	#include <winsock2.h>
	#define in_addr_t unsigned long
	#define socklen_t int
#else
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <unistd.h>
#endif

#include <string.h>

#include "Tools/Exception.hpp"

proZPRd::TCPSocketServer::TCPSocketServer(const std::string & Ip, const unsigned short Port): Ip(Ip), Port(Port)
{
	/**
		Inicjalizacja WinSock
	*/
	#if defined(_WIN32)
		WSADATA WinsockData;
		if(WSAStartup(MAKEWORD(2, 2), &WinsockData) != 0)
			throw Tools::Exception(EXCEPTION_PARAMS, "WSAStartup() failed");
	#endif
	
	/**
		IP -> liczba
	*/
	in_addr_t BindIp = inet_addr(Ip.c_str());
	if(BindIp == (in_addr_t) -1)
		throw Tools::Exception(EXCEPTION_PARAMS, "Cannot convert address to struct");
	
	/**
		Port -> zmieniona kolejność bitów
	*/
	const unsigned short ListenPort = htons(Port);
	
	/**
		Struktura do wykonania ::bind
	*/
	struct sockaddr_in BindStruct;
	memset(&BindStruct, 0, sizeof(sockaddr_in));
	BindStruct.sin_family = AF_INET;
	BindStruct.sin_port = ListenPort;
	BindStruct.sin_addr.s_addr = BindIp;
	
	Socket = socket(AF_INET, SOCK_STREAM, 0);
	if(Socket <= 0)
		throw Tools::Exception(EXCEPTION_PARAMS, "Cannot open socket");
	
	int ReuseAddr = 1;
	if(setsockopt(Socket, SOL_SOCKET, SO_REUSEADDR, &ReuseAddr, sizeof(ReuseAddr)) != 0)
		throw Tools::Exception(EXCEPTION_PARAMS, "Cannot set SO_REUSEADDR");

	if(bind(Socket, (sockaddr*) &BindStruct, sizeof(BindStruct)) != 0)
		throw Tools::Exception(EXCEPTION_PARAMS, "Cannot bind to socket");
	
	if(listen(Socket, BackLogSize) != 0)
		throw Tools::Exception(EXCEPTION_PARAMS, "Cannot listen socket");
}
proZPRd::TCPSocketServer::~TCPSocketServer()
{
	#if defined(_WIN32)
		closesocket(Socket);
	#else
		close(Socket);
	#endif
}
void proZPRd::TCPSocketServer::Main(NewClient_f AcceptFunction) const
{
	while(true)
	{
		fd_set SocketSet; FD_ZERO(&SocketSet); FD_SET(Socket, &SocketSet);
		if(select(Socket + 1, &SocketSet, NULL, NULL, NULL) != 1)
		{
			if(errno == EINTR)
				return;
			
			throw Tools::Exception(EXCEPTION_PARAMS, "accept() failed");
		}
		
		struct sockaddr_in NewSocketRemoteAddress;
		socklen_t NewSocketRemoteAddressLength = sizeof(NewSocketRemoteAddress);
		int NewSocket = accept(Socket, (struct sockaddr *) &NewSocketRemoteAddress, &NewSocketRemoteAddressLength);
		if(NewSocket <= 0)
			throw Tools::Exception(EXCEPTION_PARAMS, "accept() failed");
		
		AcceptFunction(std::unique_ptr<TCPSocketClient>(new TCPSocketClient(NewSocket, NewSocketRemoteAddress)));
	}
}
