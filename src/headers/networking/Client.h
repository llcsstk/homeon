#pragma once
#ifndef CORE_SERVER_CLIENT
#define CORE_SERVER_CLIENT

#include <thread>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/bind.hpp>


using boost::asio::ip::tcp;

typedef struct cs_c_info
{
	uint16_t client_id;
	uint16_t timestamp;
} CSClientConnectionInfo;

class CSClient :
	public std::enable_shared_from_this<CSClient>
{
private:
	tcp::socket socket_;
	std::thread ping_thread;
	boost::asio::deadline_timer input_deadline_;
	CSClientConnectionInfo* cinfo;
	std::array<char, 1024> recv_buffer;
	
	bool isActive;
	
	void StartRead();
	bool disconnected() const;
	void check_deadline(boost::asio::deadline_timer* deadline);
public:
	CSClient(tcp::socket socket);
	uint16_t GetClientId();
	
	void Start();
	void HandlePacket(std::array<char, 1024> packet);
	void SendWelcome();
	void SendPing();
	void SendSimpleAction(uint8_t value);
	
	void CloseClient();
	void StartPingControl();
};

#endif // !CSClient