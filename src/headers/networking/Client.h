#pragma once
#ifndef CORE_SERVER_CLIENT
#define CORE_SERVER_CLIENT

#include <iostream>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>

typedef struct cs_c_info
{
	boost::asio::ip::tcp::socket *csock;
	std::string ip;
	unsigned long conn_timestamp;
	unsigned long last_request;
} CSClientConnectionInfo;

class CSClient
{
private:
	CSClientConnectionInfo *cinfo;

public:
	CSClient(boost::asio::ip::tcp::socket *csock_);
	void write_handler(const boost::system::system_error& ec, std::size_t bytes_transferred);
	void SendWelcome();
	void CloseClient();
	void SendStrangePacket();
	void SendPing();
};

#endif // !CSClient