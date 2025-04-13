#pragma once

#include <boost/beast/http/message.hpp>
#include <boost/beast/http/string_body.hpp>
#include <unordered_map>

namespace AuditTrail::MVC
{
	class Controller;
}

using namespace boost::beast;

namespace AuditTrail::Core
{
	class RequestRouter
	{
	private:
		std::unordered_map<std::string, int> f;

	public:
		void HandleRequest(http::request<http::string_body> request);
	};
} // namespace AuditTrail::Core