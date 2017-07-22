#include "../../headers/networking/Server.h"
#include "../../headers/networking/Client.h"

using namespace std;

CoreSERVER::CoreSERVER()
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

	boost::asio::io_service io_service;
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), (unsigned short)CORESERVER_TCP_PORT);
	boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint);

	while (true)
	{
		try
		{
			boost::asio::ip::tcp::socket socket(io_service);
			acceptor.accept(socket, endpoint);
			
			CSClient* client = new CSClient(&socket);
			/*client->SendWelcome();
			client->SendPing();*/
			client->CloseClient();
		}
		catch (boost::system::system_error const& e)
		{
			std::cout << "Warning: could not connect : " << e.what() << std::endl;
		}
	}
}