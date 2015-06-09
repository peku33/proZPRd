#include "ServerThread.hpp"

#include "Logger.hpp"
#include "Tools/Exception.hpp"
#include "HTTPRequest.hpp"

proZPRd::ServerThread::ServerThread(const unsigned int ThisThreadId, const volatile bool * ShouldExit, const HTTPRequestProcessor & HRP, std::queue<TCPSocketServer::NewClientPtr_t> & NewClientsQueue, std::mutex & NewClientsQueueMutex, std::condition_variable & NewClientsNewData):
	ThisThreadId(ThisThreadId), ShouldExit(ShouldExit), HRP(HRP),
	NewClientsQueue(NewClientsQueue), NewClientsQueueMutex(NewClientsQueueMutex), NewClientsNewData(NewClientsNewData),
	MainThread(&proZPRd::ServerThread::Main, this)
{
	Logger::Info("Thread #" + std::to_string(ThisThreadId) + " starting");
}
proZPRd::ServerThread::~ServerThread()
{
	Logger::Info("Thread #" + std::to_string(ThisThreadId) + " waiting for finish");
	MainThread.join();
	Logger::Info("Thread #" + std::to_string(ThisThreadId) + " finished");
}
void proZPRd::ServerThread::Main()
{
	while(!*ShouldExit)
	{
		std::unique_lock<std::mutex> NewClientsQueueLock(NewClientsQueueMutex);
		
			/**
				Jeśli kolejka jest pusta, to uruchamiamy oczekiwanie na zmiennej warunkowej
			*/
			if(NewClientsQueue.size() == 0)
				NewClientsNewData.wait(NewClientsQueueLock);
			
			/**
				W tym miejscu spędziłem bite 4 godziny.
				Jak się okazuje, wątek może obudzić się również "samodzielnie" - linia wyżej odblokowywała wątek, przechodziła niżej, pobierała wskaźnik i kończyliśmy z segmentation fault.
				Super cool.
			*/
			if(NewClientsQueue.size() == 0)
				continue;
			
			/**
				Wyciągamy Socket z kolejki
			*/
			std::unique_ptr<TCPSocketClient> ThisClient = std::move(NewClientsQueue.front()); NewClientsQueue.pop();
		
		NewClientsQueueLock.unlock();
		
		
		/**
			Bufor który będzie przyjmował do siebie przychodzące dane
		*/
		static const unsigned int InputBufferSize = 1024;
		char InputBuffer[InputBufferSize];
		std::string Request;
		
		while(true)
		{
			std::size_t InputLength = 0;
			
			try
			{
				InputLength = ThisClient->Read(InputBuffer, InputBufferSize);
			}
			catch(...) { break; }
			
			Request.append(InputBuffer, InputLength);
			
			/**
				Sprawdzamy, czy dostaliśmy już wszystkie potrzebne dane, jeśli nie - zbieramy dane dalej.
			*/
			try
			{
				HTTPRequest HR = HTTPRequest::TryParse(Request); ///To może rzucić wyjątek, że jeszcze nie gotowe
				Logger::Info("Thread #" + std::to_string(ThisThreadId) + ", client: " + ThisClient->GetRemoteIpPortStr() + " requested: " + HR.GetURL() + " from: " + HR.GetHost());
				HTTPResponse::HTTPResponsePtr Response = HRP.Process(HR);
				std::string ResponeStr = Response->CreateResponse();
				ThisClient->Write(ResponeStr.c_str(), ResponeStr.length());
				break;
			}
			catch(HTTPRequest::HTTPRequestNotComplete &) {}
			catch(std::exception & E) { Logger::Error("Thread #" + std::to_string(ThisThreadId) + ": " + E.what()); break; }
		}
	}
}
