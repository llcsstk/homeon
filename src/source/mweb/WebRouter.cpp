#include "src/headers/mweb/WebRouter.h"
#include "src/headers/database/dao/DAOSensores.h"

#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "src/headers/json/serializer/SensorSerializer.h"

#include <thread>

namespace json = rapidjson;

WebRouter::WebRouter()
{
	crow::logger::setLogLevel(crow::LogLevel::CRITICAL);
	
	CROW_ROUTE(app, "/")
    ([](const crow::request&, crow::response& response_) 
	{
		response_.write("teste");
		response_.end();
	});
}

void WebRouter::start_app()
{
	registerSensorRoute();
	
	app.port(18080).multithreaded().run();
}

void WebRouter::Start()
{
	std::thread web_t(&WebRouter::start_app, this);
	web_t.detach();
}

void WebRouter::RegisterResponse(crow::response* response_)
{
	response_->set_header("Content-Type", "application/json");
	response_->set_header("Server", "HomeOn/0.1 (Crow)");
}

void WebRouter::registerSensorRoute()
{
	CROW_ROUTE(app, "/sensores")
    ([&](const crow::request&, crow::response& response_) 
	{
		json::StringBuffer buffer;
		json::Writer<json::StringBuffer> writer(buffer);
		
		sql::Connection* con = MySQLConnector::getManager()->getConnection();
		sql::ResultSet* sensores = GetAllSensores(con);
		
		serializeList(&writer, sensores);
		
		delete con;
		delete sensores;
		
		WebRouter::RegisterResponse(&response_);
		response_.write(buffer.GetString());
		response_.end();
	});
}