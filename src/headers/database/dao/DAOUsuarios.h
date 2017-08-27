#ifndef DAO_USUARIOS
#define DAO_USUARIOS

#include "src/headers/database/mysql_manager.h"
#include "src/headers/usuarios/usuario.h"

static Usuario* m_Usuarios[1] = {
	new Usuario
	{
	.codigo = 1,
	.login = "lucas",
	.senha = "1234",
	.perfil = "Dono",
	.nome = "Lucas Leite"
	}
};

class DAOUsuario
{
public:
	static DAOUsuario* GetDAO();
	Usuario* Login(std::string login, std::string passwd);
private:
	static DAOUsuario* m_This;
};

#endif