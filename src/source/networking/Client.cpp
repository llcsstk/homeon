#include "../../headers/networking/Client.h"
#include "../../headers/logging/Logger.h"

CSClient::CSClient(tcp::socket socket)
    : socket_(std::move(socket))
{
	/*cinfo = new cs_c_info();
	cinfo->ip_address = csock_->remote_endpoint().address().to_string();
	cinfo->csock = csock_;
	
	cinfo->csock->async_read_some(boost::asio::buffer(recv_buffer, 512), boost::bind(&CSClient::handle_receive, shared_from_this(),
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));*/

	CLogger::GetLogger()->Log("Client connected ");
	//CLogger::GetLogger()->Log("Client connected %s", cinfo->ip_address.c_str());

}

void CSClient::start()
{
	auto self(shared_from_this());
	
	boost::asio::async_read(socket_,
        boost::asio::buffer(recv_buffer),
		boost::asio::transfer_at_least(1),
        [this, self](boost::system::error_code ec, std::size_t)
        {
          if (!ec)
          {
			  std::cout << "sending response " << std::endl;
			send_result(recv_buffer[1]);
          }
          else
          {
            std::cout << "Error reading data; Code: " << ec << std::endl;
          }
        });
}

void CSClient::send_result(char value)
{
	char result[1];
	result[0] = (char) ((int) value) * 2;
	
    auto self(shared_from_this());
    boost::asio::async_write(socket_,
        boost::asio::buffer(result,
          sizeof(result)),
        [this, self](boost::system::error_code ec, std::size_t )
        {
          if (!ec)
          {
			std::cout << "send successfully" << std::endl; 
          }
          else
          {
            std::cout << "error sending" << std::endl;
          }
        });
  }

void CSClient::handle_receive(const boost::system::error_code error, size_t bytes_transferred)
{
	if(!error)
	{
	    std::cout << "ulala" << std::endl;
		std::cout << "Received: '" << std::string(recv_buffer.begin(), recv_buffer.begin()+bytes_transferred) << "'\n";	
	}
	else
	{
		std::cout << "error" << std::endl;
	}
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
	//CLogger::GetLogger()->Log("Terminating existing client with ip %s", cinfo->ip_address.c_str());
	//cinfo->csock->close();
	socket_.close();

	//free memory alloc struct
	//delete cinfo;
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