#include "../../headers/networking/Client.h"
#include "../../headers/logging/Logger.h"

CSClient::CSClient(boost::asio::ip::tcp::socket *csock_)
{
	cinfo = (CSClientConnectionInfo*)malloc(sizeof(CSClientConnectionInfo));
	cinfo->ip = csock_->remote_endpoint().address().to_string();
	cinfo->csock = csock_;

	CLogger::GetLogger()->Log("Client connected %s", cinfo->ip.c_str());
}

void CSClient::write_handler(const boost::system::system_error & ec, std::size_t bytes_transferred)
{
}

/*void CSClient::SendWelcome()
{
	p_welcome* welcome = (p_welcome*)malloc(sizeof(p_welcome));
	welcome->header = (p_header*)malloc(sizeof(p_header));
	welcome->header->checksum = 1;
	welcome->header->timestamp = 1;
	welcome->header->device = 5;
	//welcome->message_size = 50;
	strcpy_s(welcome->message, "Welcome from HomeOn Central");

	char buffer[sizeof(p_welcome)];
	serialize(welcome, buffer);

	boost::asio::async_write(*cinfo->csock,
		boost::asio::buffer(buffer, sizeof(p_welcome)),
		boost::bind(&CSClient::write_handler, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}*/

void CSClient::CloseClient()
{
	CLogger::GetLogger()->Log("Terminating existing client with ip %s", cinfo->ip.c_str());
	cinfo->csock->close();

	//free memory alloc struct
	free(cinfo);
}

void CSClient::SendStrangePacket()
{
	//nothing
}

/*void CSClient::SendPing()
{
	p_ping* ping = (p_ping*)malloc(sizeof(p_ping));
	ping->header = (p_header*)malloc(sizeof(p_header));
	ping->header->checksum = 1;
	ping->header->timestamp = 1;
	ping->header->device = 5;
	ping->ping = 10;

	char buffer[sizeof(p_ping)];
	serialize(ping, buffer);

	SendPacketToClient(cinfo, buffer);
}*/

/*void* SendPacketToClient(CSClientConnectionInfo *client, char* buffer)
{
	boost::asio::async_write(*client->csock, boost::asio::buffer(buffer, sizeof(buffer)), boost::bind(&CSClient::write_handler, this,
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));
}*/