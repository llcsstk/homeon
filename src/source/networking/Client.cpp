#include "../../headers/networking/Client.h"
#include "../../headers/networking/ServerPackets.h"
#include "../../headers/networking/ClientPackets.h"
#include "../../headers/networking/ClientManager.h"
#include "../../headers/logging/Logger.h"


CSClient::CSClient(tcp::socket socket)
	//: socket_(std::move(socket))
    : socket_(std::move(socket)), 
	ping_thread(&CSClient::StartPingControl, this),
	input_deadline_(socket_.get_io_service())
{
	cinfo = new CSClientConnectionInfo();
	cinfo->client_id = -1;
	cinfo->timestamp = -1;
	
	isActive = true;

	input_deadline_.expires_at(boost::posix_time::pos_infin);
}

uint16_t CSClient::GetClientId()
{
	return cinfo->client_id;
}

void CSClient::Start()
{
	CSClient::ping_thread.detach();

	CSClient::StartRead();
	
	input_deadline_.async_wait(
        boost::bind(&CSClient::check_deadline,
        shared_from_this(), &input_deadline_));
}

void CSClient::StartRead()
{
	auto self(shared_from_this());
	
	input_deadline_.expires_from_now(boost::posix_time::seconds(5));
	
	boost::asio::async_read(socket_,
	boost::asio::buffer(recv_buffer),
	boost::asio::transfer_at_least(0x0001),
	[this, self](boost::system::error_code const& ec, std::size_t recv_size)
	{
		 if ((boost::asio::error::eof == ec) ||
			(boost::asio::error::connection_reset == ec))
		{
			std::cout << "Error reading data; Code: " << ec << std::endl;
			CSClient::CloseClient();
		}
		else
		{
			CSClient::HandlePacket(std::move(recv_buffer));
			CSClient::StartRead();
		}
	});
}

void CSClient::SendWelcome()
{
	auto self(shared_from_this());
	
	Packet* welcome_packet = ServerPackets::Welcome(new Packet(cinfo));
	
    boost::asio::async_write(socket_,
	boost::asio::buffer(welcome_packet->data(),
	welcome_packet->length()),
    [this, self](boost::system::error_code ec, std::size_t transmited)
	{
		if (!ec)
		{
			//CLogger::GetLogger()->Log("Sending Welcome Back Packet with %d bytes", transmited);
		}
		else
		{
			CSClient::CloseClient();
		}
	});
}

void CSClient::SendPing()
{
	if(!isActive)
		return;

	auto self(shared_from_this());
	
	Packet* welcome_packet = ServerPackets::Ping(new Packet(cinfo));
	
    boost::asio::async_write(socket_,
	boost::asio::buffer(welcome_packet->data(),
	welcome_packet->length()),
    [this, self](boost::system::error_code ec, std::size_t transmited)
	{
		if (!ec)
		{
			//CLogger::GetLogger()->Log("Sending Ping Packet with %d bytes", transmited);
		}
		else
		{
			CSClient::CloseClient();
		}
	});
}

void CSClient::SendSimpleAction(uint8_t value)
{
	auto self(shared_from_this());
	
	Packet* simple_action_packet = ServerPackets::SimpleAction(new Packet(cinfo), value);
	
    boost::asio::async_write(socket_,
	boost::asio::buffer(simple_action_packet->data(),
	simple_action_packet->length()),
    [this, self](boost::system::error_code ec, std::size_t transmited)
	{
		if (!ec)
		{
			//CLogger::GetLogger()->Log("Sending Simple Action Packet with %d bytes", transmited);
		}
		else
		{
			CSClient::CloseClient();
		}
	});
}

void CSClient::HandlePacket(std::array<char, 1024> packet)
{
	switch((uint8_t) packet[0x0004])
	{
		case WELCOME_PACKET:
		{
			uint8_t client_id_1 = ((uint8_t) packet[0x0000]);
			uint8_t client_id_2 = ((uint8_t) packet[0x0001]);
			
			cinfo->client_id = ((uint16_t) client_id_1 << 8) | client_id_2;
			
			//CLogger::GetLogger()->Log("Welcome Packet received from client %d", cinfo->client_id);
			CLogger::GetLogger()->Log("	-> Client [%d] registered successfully!", cinfo->client_id);
			CSClient::SendWelcome();
		}
		break;
		case PING_PACKET:
		{
			//nothing to do
		}
		break;
		default:
			CLogger::GetLogger()->Log("Invalid Packet received from client %d. Packet OPCode %d", cinfo->client_id, (int) packet[0x0004]);
			break;
	}
}

void CSClient::StartPingControl()
{
	while(isActive)
	{
		sleep(2);
		
		SendPing();
	}

}

void CSClient::CloseClient()
{
	isActive = false;
	
	input_deadline_.cancel();
	
	CLogger::GetLogger()->Log("	Closing Client [%d] ", cinfo->client_id);
	ClientManager::GetManager()->UnregisterClient(shared_from_this());
}

bool CSClient::disconnected() const
{
	return !socket_.is_open();
}

void CSClient::check_deadline(boost::asio::deadline_timer* deadline)
{
	if (CSClient::disconnected())
		return;

	if (deadline->expires_at() <= boost::asio::deadline_timer::traits_type::now())
	{
		CSClient::CloseClient();
	}
	else
	{
		deadline->async_wait(
		boost::bind(&CSClient::check_deadline,
		shared_from_this(), deadline));
	}
}