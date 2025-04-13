#pragma once

#include <memory>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core/tcp_stream.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/string_body.hpp>

using namespace boost::asio;
using namespace boost::beast;

namespace AuditTrail::Core
{
	class Session : public std::enable_shared_from_this<Session>
	{
	private:
		tcp_stream stream;
		flat_buffer buffer;
		http::request<http::string_body> request;

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