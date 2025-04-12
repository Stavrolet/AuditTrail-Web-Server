#include "Session.h"

namespace AuditTrail
{
	void Session::DoRead()
	{
		http::async_read(stream, buffer, request, [self = shared_from_this()] (error_code ec, std::size_t)
		{
			if (!ec)
				self->HandleRequest();
		});
	}

	void Session::HandleRequest()
	{
		response.version(request.version());
		response.keep_alive(request.keep_alive());
		response.result(http::status::ok);
		response.set(http::field::server, "AuditTrail Boost.Best Server");
		response.set(http::field::content_type, "text/plain");
		response.body() = "Hello from Beast!\n";
		response.prepare_payload();

		http::async_write(stream, response, [self = shared_from_this()] (error_code ec, std::size_t)
		{
			self->stream.socket().shutdown(ip::tcp::socket::shutdown_send, ec);
		});
	}
}