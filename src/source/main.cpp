#include "../headers/networking/Server.h"

int main()
{
	CLogger::GetLogger()->Log("HomeOn.Central Bootstrap is initializing");

	boost::asio::io_service io_service;
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), (unsigned int) CORESERVER_TCP_PORT);

	CoreSERVER* core = new CoreSERVER(io_service, endpoint);
	core->Listen();

	io_service.run();
	return 0;
}