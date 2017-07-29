#include "src/headers/database/dao/DAOSensores.h"

sql::ResultSet* GetAllSensores(sql::Connection *con)
{
	sql::Statement *stmt;
	sql::ResultSet *res;
	
	con->setSchema("homeon");

	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT * FROM SENSOR");
	
	return res;
}