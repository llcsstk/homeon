#ifndef SENSOR
#define SENSOR

#include <stdlib.h>

typedef struct t_sensor
{
	uint16_t codigo;
	std::string descricao;
}TipoSensor;

typedef struct sensor
{
	uint16_t codigo;
	std::string nome;
	t_sensor tipo;
	std::string ip;
}Sensor;

#endif