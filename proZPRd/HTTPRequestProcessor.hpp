#pragma once

#include "Tools/NoCopyU.hpp"

#include <unordered_map>
#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"

namespace proZPRd
{
	class HTTPRequestProcessor : public Tools::NoCopyU
	{
		public:
			typedef std::unordered_map<std::string, std::string> HostMapping_t;
			
		public:
			HTTPRequestProcessor(const HostMapping_t & HostMapping);
		
		private:
			const HostMapping_t & HostMapping;
		
		public:
			HTTPResponse::HTTPResponsePtr Process(const HTTPRequest & HR) const;
		
		private:
			static bool IsURLValid(const std::string & URL);
	};
}