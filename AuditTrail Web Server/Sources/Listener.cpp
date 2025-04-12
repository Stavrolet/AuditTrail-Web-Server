#include "Listener.h"

namespace AuditTrail
{
	Listener::Listener(io_context& ioc, ip::tcp::endpoint endpoint):
		acceptor(ioc), socket(ioc)
	{
		acceptor.open(endpoint.protocol());
		acceptor.set_option(socket_base::reuse_address(true));
		acceptor.bind(endpoint);
		acceptor.listen();
	}

	void Listener::DoAccept()
	{
		acceptor.async_accept(socket, [self = shared_from_this()] (error_code ec)
		{
			if (!ec) std::make_shared<Session>(std::move(self->socket))->Run();
			self->DoAccept();
		});
	}
}