#include "Session.h"

namespace AuditTrail::Core
{
	class Listener : public std::enable_shared_from_this<Listener>
	{
	private:
		ip::tcp::acceptor acceptor;
		ip::tcp::socket socket;

	public:
		Listener(io_context& ioc, ip::tcp::endpoint endpoint);

		void Run()
		{
			DoAccept();
		}

	private:
		void DoAccept();
	};
}