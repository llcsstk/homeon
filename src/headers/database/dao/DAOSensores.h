#ifndef DAO_SENSORES
#define DAO_SENSORES

#include "src/headers/database/mysql_manager.h"
#include "src/headers/sensores/sensor.h"

sql::ResultSet* GetAllSensores(sql::Connection* con);

static Sensor* m_Sensores[2] = {
	new Sensor
	{
	.codigo = 1,
	.nome = "Teste"
	},
	new Sensor
	{
	.codigo = 2,
	.nome = "Teste"
	}};

#endif