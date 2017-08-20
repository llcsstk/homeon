#ifndef WEB_ROUTER
#define WEB_ROUTER

#include "crow.h"

class WebRouter
{
private:
	crow::SimpleApp app;
	void start_app();
	void registerSensorRoute();
	void RegisterActualTemperature();
	void RegisterSensorAction();
	void RegisterResponse(crow::response* response_);
public:
	WebRouter();
	void Start();
};



#endif