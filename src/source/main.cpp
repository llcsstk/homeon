#include "../headers/networking/Server.h"

int main()
{
	CLogger::GetLogger()->Log("HomeOn.Central Bootstrap is initializing");

	CoreSERVER* core = new CoreSERVER();
	core->Listen();

	system("pause");
	return 0;
}