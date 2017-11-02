#ifndef USUARIOSERIALIZER
#define USUARIOSERIALIZER

#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "src/headers/usuarios/usuario.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

namespace json = rapidjson;

class UsuarioSerializer
{
public:
	static UsuarioSerializer* GetSerializer();
	void serialize(json::Writer<json::StringBuffer>* writer, Usuario* usr);
private:
	static UsuarioSerializer* m_This;
};

#endif