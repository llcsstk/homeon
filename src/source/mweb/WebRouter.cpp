#include "src/headers/mweb/WebRouter.h"
#include "src/headers/database/dao/DAOSensores.h"

#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "src/headers/sensores/SensorManager.h"
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
	RegisterActualTemperature();
	RegisterSensorAction();
	
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

void WebRouter::RegisterActualTemperature()
{
	CROW_ROUTE(app, "/temperaturaAtual")
    ([&](const crow::request&, crow::response& response_) 
	{
		WebRouter::RegisterResponse(&response_);
		response_.write("{\n	temperatura:15c\n}");
		response_.end();
	});
}

void WebRouter::RegisterSensorAction()
{
	CROW_ROUTE(app, "/acaoSensor")
	.methods("POST"_method)
	([](const crow::request& req)
	{
		auto x = crow::json::load(req.body);
		
		if (!x)
			return crow::response(400);
			
		int codigoSensor = x["codigoSensor"].i();
		int action = x["action"].i();
		
		bool sended = HandleNewAction(codigoSensor, action);
		
		/*int sum = x["a"].i()+x["b"].i();
		std::ostringstream os;
		os << sum;
		return crow::response{os.str()};*/
		if(sended)
			return crow::response(200);
		else 
			return crow::response(400);
	});
}

void WebRouter::registerSensorRoute()
{
	CROW_ROUTE(app, "/sensores")
    ([&](const crow::request&, crow::response& response_) 
	{
		/*json::StringBuffer buffer;
		json::Writer<json::StringBuffer> writer(buffer);
		
		sql::Connection* con = MySQLConnector::getManager()->getConnection();
		sql::ResultSet* sensores = GetAllSensores(con);
		
		serializeList(&writer, sensores);
		
		delete con;
		delete sensores;*/
		
		json::StringBuffer buffer;
		json::Writer<json::StringBuffer> writer(buffer);
		
		serializeList(&writer, m_Sensores);
		
		WebRouter::RegisterResponse(&response_);
		//response_.write("{\n	{\n		codigo:1\n		nome:'Sensor Teste',\n		situacao:1\n	}\n}");
		response_.write(buffer.GetString());
		response_.end();
	});
}