#include <iostream>
#include <thread>
#include <vector>
#include <memory>

#include "Listener.h"
#include "TypeDefs.h"

using namespace AuditTrail;

int main()
{
	try
	{
		const ip::address address = ip::make_address("0.0.0.0");
		const uint16 port = 9099;
		const int32 threads = std::thread::hardware_concurrency();

		io_context ioc{ threads };

		std::make_shared<Listener>(ioc, ip::tcp::endpoint{ address, port })->Run();

		std::vector<std::thread> thread_pool;
		for (int i = 0; i < threads; ++i)
		{
			thread_pool.emplace_back([&ioc]
			{
				ioc.run();
			});
		}

		for (auto& t : thread_pool)
			t.join();
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Fatal: " << ex.what() << std::endl;
	}
}
