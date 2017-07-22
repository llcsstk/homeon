#pragma once
#ifndef CORE_SERVER
#define CORE_SERVER

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "../logging/Logger.h"
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>

#define CORESERVER_TCP_PORT 1500

class CoreSERVER
{
public:
	CoreSERVER();
	void Listen();
};

#endif // !CORE_SERVER