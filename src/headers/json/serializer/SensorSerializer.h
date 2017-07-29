#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include <cppconn/resultset.h>

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

void serializeList(json::Writer<json::StringBuffer>* writer, sql::ResultSet* rs)
{
	writer->StartArray();
	while(rs->next())
	{
		serialize(writer, rs);
	}
	writer->EndArray();
}