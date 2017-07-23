#pragma once
#ifndef CORE_SERVER
#define CORE_SERVER

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "../logging/Logger.h"
#include "Client.h"
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>

using boost::asio::ip::tcp;

#define CORESERVER_TCP_PORT 1500

class CoreSERVER
{
private:
	tcp::acceptor acceptor_;
	tcp::socket socket_;
public:
	CoreSERVER(boost::asio::io_service& io_service, const boost::asio::ip::tcp::endpoint& endpoint);
	void Listen();
	void handle_accept(CSClient* session, const boost::system::error_code& error);
};

#endif // !CORE_SERVER