#pragma once

#include <memory>
#include <boost/asio.hpp>
#include <boost/beast.hpp>

using namespace boost::asio;
using namespace boost::beast;

namespace AuditTrail
{
	class Session : public std::enable_shared_from_this<Session>
	{
	private:
		tcp_stream stream;
		flat_buffer buffer;
		http::request<http::string_body> request;
		http::response<http::string_body> response;

	public:
		explicit Session(ip::tcp::socket socket): stream(std::move(socket))
		{ }

		void Run()
		{
			DoRead();
		}

	private:
		void DoRead();
		void HandleRequest();
	};
} // namespace AuditTrail