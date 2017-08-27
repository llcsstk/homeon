#include "src/headers/database/dao/DAOUsuarios.h"

#include <string.h>
#include <boost/algorithm/string.hpp>

DAOUsuario* DAOUsuario::m_This = NULL;

DAOUsuario* DAOUsuario::GetDAO()
{
	if(m_This == NULL)
		m_This = new DAOUsuario();
	return m_This;
}

Usuario* DAOUsuario::Login(std::string login, std::string passwd)
{
	for (uint16_t u_index = 0; u_index < (sizeof(m_Usuarios) / sizeof(m_Usuarios[0])); u_index++)
	{
		Usuario* usr = m_Usuarios[u_index];
		
		//if(strcmp(usr->login.c_str(), login.c_str()) == 0 && strcmp(usr->senha.c_str(), passwd.c_str()) == 0)
		if(boost::iequals(usr->login, login) && boost::iequals(usr->senha, passwd))
			return usr;
	}
	return NULL;
}