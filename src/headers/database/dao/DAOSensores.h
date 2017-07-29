#ifndef DAO_SENSORES
#define DAO_SENSORES

#include "src/headers/database/mysql_manager.h"

sql::ResultSet* GetAllSensores(sql::Connection* con);

#endif