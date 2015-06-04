#include "Server.hpp"

#include <signal.h>
#include "Logger.hpp"
#include "Tools/Exception.hpp"
#include <string.h>

proZPRd::Server::Server(const std::string & ListenAddressStr, const unsigned short ListenPort, const unsigned int ThreadsNum, const HTTPRequestProcessor & HRP): HRP(HRP), TSS(ListenAddressStr, ListenPort), ShouldExit(false)
{
	signal(SIGINT, &proZPRd::Server::SignalHandler);
	signal(SIGTERM, &proZPRd::Server::SignalHandler);
	
	for(unsigned int I = 0; I < ThreadsNum; I++)
		Threads.push_back(std::unique_ptr<ServerThread>(new ServerThread(I, &ShouldExit, HRP, NewClientsQueue, NewClientsQueueMutex, NewClientsNewData)));
}
proZPRd::Server::~Server()
{
	ShouldExit = true;
	
	NewClientsNewData.notify_all();
	
	Threads.clear();
}
void proZPRd::Server::Run()
{
	TSS.Main(std::bind(&proZPRd::Server::OnNewClient, this, std::placeholders::_1));
}
void proZPRd::Server::SignalHandler(int)
{
	
}
void proZPRd::Server::OnNewClient(TCPSocketServer::NewClientPtr_t NewClient)
{
	if(!NewClient)
		throw Tools::Exception(EXCEPTION_PARAMS, "NewClient is null");
	
	std::unique_lock<std::mutex> NewClientsQueueLock(NewClientsQueueMutex);
	
		NewClientsQueue.emplace(std::move(NewClient));
		NewClientsNewData.notify_one();
	
	NewClientsQueueLock.unlock();
}