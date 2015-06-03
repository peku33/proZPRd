#include "ServerThread.hpp"

#include "Logger.hpp"
#include <boost/asio/error.hpp>
#include "HTTPRequest.hpp"

proZPRd::ServerThread::ServerThread(const unsigned int ThisThreadId, const volatile bool * ShouldExit, std::queue<boost::asio::ip::tcp::socket> & SocketQueue, std::mutex & SocketQueueMutex, std::condition_variable & SocketQueueNotEmpty):
	ThisThreadId(ThisThreadId), ShouldExit(ShouldExit),
	SocketQueue(SocketQueue), SocketQueueMutex(SocketQueueMutex), SocketQueueNotEmpty(SocketQueueNotEmpty),
	MainThread(&proZPRd::ServerThread::Main, this)
{
	Logger::Ok("Thread #" + std::to_string(ThisThreadId) + " starting");
}
proZPRd::ServerThread::~ServerThread()
{
	Logger::Info("Thread #" + std::to_string(ThisThreadId) + " waiting for finish");
	MainThread.join();
	Logger::Ok("Thread #" + std::to_string(ThisThreadId) + " finished");
}
void proZPRd::ServerThread::Main()
{
	while(!*ShouldExit)
	{
		std::unique_lock<std::mutex> SocketQueueLock(SocketQueueMutex, std::defer_lock);
		
		SocketQueueLock.lock();
		
			if(SocketQueue.size() == 0)
				SocketQueueNotEmpty.wait(SocketQueueLock);
				
			if(*ShouldExit)
				continue;
			
			boost::asio::ip::tcp::socket ThisSocket = std::move(SocketQueue.front()); SocketQueue.pop();
		
		SocketQueueLock.unlock();
		
		Logger::Ok("Thread #" + std::to_string(ThisThreadId) + " processing request");
		
		static const unsigned int InputBufferSize = 1024;
		char InputBuffer[InputBufferSize];
		std::string Request;
		
		while(true)
		{
			try
			{
				std::size_t InputLength = ThisSocket.read_some(boost::asio::buffer(InputBuffer, InputBufferSize));
				Request.append(InputBuffer, InputLength);
				
				try
				{
					HTTPRequest HR = HTTPRequest::TryParse(Request);
					break;
				}
				catch(HTTPRequest::HTTPRequestNotComplete &) {}
			}
			catch(boost::system::system_error &)
			{
				break;
			}
		}
		
		ThisSocket.close();
		
		Logger::Ok("Thread #" + std::to_string(ThisThreadId) + " processing end, socket closed");
	}
}