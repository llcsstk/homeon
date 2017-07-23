#include "../../headers/networking/Server.h"
#include "../../headers/networking/Client.h"

using namespace std;

CoreSERVER::CoreSERVER(boost::asio::io_service& io_service,
      const tcp::endpoint& endpoint)
    : acceptor_(io_service, endpoint),
      socket_(io_service)
{
	try
	{
		CLogger::GetLogger()->Log("HomeOn.Central CoreServer initializing");
	}
	catch (std::exception& e) // 6
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}

void CoreSERVER::Listen()
{
	CLogger::GetLogger()->Log("HomeOn.Central CoreServer listening ON port %d ...", CORESERVER_TCP_PORT);

	try
	{
		acceptor_.async_accept(socket_,
			[this](boost::system::error_code ec)
			{
			  if (!ec)
			  {
				std::make_shared<CSClient>(std::move(socket_))->start();
			  }
			  else
				  std::cout << "Error";

			  Listen();
			});
	}
	catch (boost::system::system_error const& e)
	{
		std::cout << "Warning: could not connect : " << e.what() << std::endl;
	}
}