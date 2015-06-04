#include "TCPSocketClient.hpp"

#include "Tools/Exception.hpp"

proZPRd::TCPSocketClient::TCPSocketClient(const int Socket, const struct sockaddr_in & RemoteAddress): Socket(Socket), RemoteAddress(RemoteAddress)
{
	
}
proZPRd::TCPSocketClient::~TCPSocketClient()
{
	#if defined(_WIN32)
		closesocket(Socket);
	#else
		close(Socket);
	#endif
}

size_t proZPRd::TCPSocketClient::Read(char * Output, const size_t MaxLength)
{
	auto Length = recv(Socket, Output, MaxLength, 0);
	if(Length <= 0)
		throw Tools::Exception(EXCEPTION_PARAMS, "read() failed");
	
	return (size_t) Length;
}
void proZPRd::TCPSocketClient::Write(const char * Input, const size_t Length)
{
	auto WrittenLength = send(Socket, Input, Length, 0);
	if(WrittenLength != (ssize_t) Length)
		throw Tools::Exception(EXCEPTION_PARAMS, "write() failed");
}
std::string proZPRd::TCPSocketClient::GetRemoteIpStr() const
{
	return std::string(inet_ntoa(RemoteAddress.sin_addr));
}
unsigned short proZPRd::TCPSocketClient::GetRemotePort() const
{	
	return ntohs(RemoteAddress.sin_port);
}
std::string proZPRd::TCPSocketClient::GetRemoteIpPortStr() const
{
	return GetRemoteIpStr() + ":" + std::to_string(GetRemotePort());
}