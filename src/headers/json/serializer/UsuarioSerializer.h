#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include <cppconn/resultset.h>
#include "src/headers/usuarios/usuario.h"


#include <iostream>
#include <stdio.h>
#include <stdlib.h>

namespace json = rapidjson;

void serialize(json::Writer<json::StringBuffer>* writer, Usuario* usr)
{
	writer->StartObject();
	writer->Key("codigo");
	writer->Uint(usr->codigo);
	writer->Key("login");
	writer->String(usr->login.c_str());
	writer->Key("nome");
	writer->String(usr->nome.c_str());
	writer->Key("perfil");
	writer->String(usr->perfil.c_str());
	writer->EndObject();
}