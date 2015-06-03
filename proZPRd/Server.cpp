#include "Server.hpp"

#include "Logger.hpp"

proZPRd::Server::Server(const std::string & ListenAddressStr, const unsigned short ListenPort, const unsigned int ThreadsNum = 0):
	ListenAddressStr(ListenAddressStr), ListenPort(ListenPort),
	IS(), SS(IS, SIGINT, SIGTERM, SIGQUIT), AC(IS, boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(ListenAddressStr), ListenPort)), NewClientSocket(IS),
	ShouldExit(false)
{
	CreateQuitter();
	CreateAcceptor();
	
	for(unsigned int I = 0; I < ThreadsNum; I++)
		ServerThreads.push_back(std::unique_ptr<ServerThread>(new ServerThread(I, &ShouldExit, SocketQueue, SocketQueueMutex, SocketQueueNotEmpty)));
	
	AC.listen();
}
void proZPRd::Server::Run()
{
	IS.run();
}
void proZPRd::Server::CreateAcceptor()
{
	AC.async_accept(NewClientSocket, [&] (const boost::system::error_code & ErrorCode)
	{
		/**
			Czy nie zatrzymał nas sygnał?
		*/
		if(!AC.is_open())
			return;
		
		/**
			Jeśli błąd, to nie kontynnujemy
		*/
		if(ErrorCode)
			return;
		
		Logger::Ok("New connection from: " + NewClientSocket.remote_endpoint().address().to_string() + ":" + std::to_string(NewClientSocket.remote_endpoint().port()));
		
		std::unique_lock<std::mutex> SocketQueueLock(SocketQueueMutex);
			
			SocketQueue.emplace(std::move(NewClientSocket));
			SocketQueueNotEmpty.notify_one();
		
		SocketQueueLock.unlock();
		
		/**
			Stwórz nowy akceptor
		*/
		CreateAcceptor();
	});
}
void proZPRd::Server::CreateQuitter()
{
	SS.async_wait([&] (const boost::system::error_code &, int)
	{
		/**
			Przestajemy przyjmować nowe połączenia
		*/
		AC.close();
		
		/**
			Ustawiamy flagę zamknięcia programu
		*/
		ShouldExit = true;
		
		/**
			Odwieszamy wszystkie procesy
		*/
		SocketQueueNotEmpty.notify_all();
		
		/**
			Zamykamy wszystkie wątki
		*/
		ServerThreads.clear();
	});
}