#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include <cppconn/resultset.h>
#include "src/headers/sensores/sensor.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

namespace json = rapidjson;

void serialize(json::Writer<json::StringBuffer>* writer, sql::ResultSet* rs)
{
	writer->StartObject();
	writer->Key("idSensor");
	writer->Int(rs->getInt("idSensor"));
	writer->Key("nome");
	writer->String(rs->getString("nome").c_str());
	writer->Key("ip");
	writer->String(rs->getString("ip").c_str());
	writer->EndObject();
}

void serialize(json::Writer<json::StringBuffer>* writer, Sensor* sen)
{
	writer->StartObject();
	writer->Key("idSensor");
	writer->Uint(sen->codigo);
	writer->Key("nome");
	writer->String(sen->nome.c_str());
	writer->Key("ip");
	writer->String(sen->ip.c_str());
	writer->EndObject();
}

void serializeList(json::Writer<json::StringBuffer>* writer, sql::ResultSet* rs)
{
	writer->StartArray();
	while(rs->next())
	{
		serialize(writer, rs);
	}
	writer->EndArray();
}

void serializeList(json::Writer<json::StringBuffer>* writer, Sensor* sensores[])
{
	writer->StartArray();
	
	for (uint16_t sensor_index = 0; sensor_index <= (sizeof(sensores) / sizeof(sensores[0])); sensor_index++)
		serialize(writer, sensores[sensor_index]);

	writer->EndArray();
}