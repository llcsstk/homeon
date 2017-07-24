#include "../headers/networking/Server.h"

#include <boost/thread.hpp>
#include <thread>
#include <string.h>

int main()
{
	CLogger::GetLogger()->Log("HomeOn.Central Bootstrap is initializing");

	boost::asio::io_service srv;
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), (unsigned int) CORESERVER_TCP_PORT);

	CoreSERVER* core = new CoreSERVER(srv, endpoint);
	core->Start();
	
	boost::thread thread(boost::bind(&boost::asio::io_service::run, &srv));
	thread.detach();
	
	while(true)
	{
		int key_pressed = std::cin.get();
		
		if(key_pressed == 0x000A)
		{
			CLogger::GetLogger()->log_console_enabled = false;
			
			while(true)
			{
				std::cout << "Console logging is disabled;" << std::endl << std::endl;
				std::cout << "Options:" << std::endl;
				std::cout << "	1-Send Simple Action" << std::endl;
				std::cout << "	2-View All clients" << std::endl << std::endl;
				std::cout << "	0-Exit action center" << std::endl;
				std::cout << "Enter action: ";
				
				std::string s;
				std::getline(std::cin, s);
				
				int option = atoi(s.c_str());
				
				switch(option)
				{
					case 1:
					{
						std::cout << std::endl;
						
						std::cout << "Informe o número do cliente: ";
						
						std::getline(std::cin, s);
						
						uint16_t client_id = static_cast<uint16_t>(std::stoi(s));
						
						std::shared_ptr<CSClient> client = ClientManager::GetManager()->GetClient(client_id);
						
						if(client == NULL)
							std::cout << "Invalid client!" << std::endl;
						else
						{
							std::cout << "Informe o valor da ação: ";
							
							std::getline(std::cin, s);
							
							int valor = std::stoi(s);
							
							ClientManager::GetManager()->GetClient(client_id)->SendSimpleAction(valor);
							
							std::cout << "Simple action sent!" << std::endl;
						}
					}
					break;
					case 2:
					{
						ClientManager::GetManager()->PrintAllClients();
					}
					break;
					default:
						break;
				}
				
				if(option == 0x00)
					break;
				
				std::cout << "Want another action? [Y/n] ";
				
				std::getline(std::cin, s);
				
				if(strcmp(s.c_str(), "Y") != 0)
				{
					break;
				}
			}
		}
		
		std::cout << std::endl << std::endl;
		std::cout << "Console Logging is enabled again" << std::endl;
		CLogger::GetLogger()->log_console_enabled = true;
	}
	
	return 0;
}