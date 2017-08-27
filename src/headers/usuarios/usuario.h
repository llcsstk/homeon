#ifndef USUARIO
#define USUARIO
/*
codigo int
login string
senha string
perfil string
*/

/*
nome
cpf
rg
datanascimento
email*/

/*struct people_data
{
	std::string nome;
	std::string cpf;
	std::string rg;
	std::string dataNascimento;
	std::string email;
};*/

typedef struct usr
{
	int codigo;
	std::string login;
	std::string senha;
	std::string perfil;
	std::string nome;
	std::string cpf;
	std::string rg;
	std::string dataNascimento;
	std::string email;
}Usuario;

#endif