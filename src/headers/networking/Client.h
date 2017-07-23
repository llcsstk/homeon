#pragma once
#ifndef CORE_SERVER_CLIENT
#define CORE_SERVER_CLIENT

#include <iostream>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>

using boost::asio::ip::tcp;

typedef struct cs_c_info
{
	boost::asio::ip::tcp::socket *csock;
	boost::asio::ip::tcp::endpoint endpoint;
	std::string ip_address;
	//unsigned long conn_timestamp;
	//unsigned long last_request;
} CSClientConnectionInfo;

class CSClient :
	public std::enable_shared_from_this<CSClient>
{
private:
	tcp::socket socket_;
	CSClientConnectionInfo* cinfo;
	std::array<char, 1024> recv_buffer;
public:
	CSClient(tcp::socket socket);
	void handle_receive(const boost::system::error_code error, size_t bytes_transferred);
	void start();
	void send_result(char value);
	void SendWelcome();
	void CloseClient();
	void SendStrangePacket();
	void SendPing();
};

#endif // !CSClient

typedef boost::shared_ptr<CSClient> client_session_ptr;