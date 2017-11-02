#include "src/headers/database/dao/DAOComodos.h"

#include <string.h>
#include <boost/algorithm/string.hpp>

DAOComodo* DAOComodo::m_This = NULL;
std::vector<Comodo*> DAOComodo::mockComodos;

DAOComodo* DAOComodo::GetDAO()
{
	if(m_This == NULL)
	{
		m_This = new DAOComodo();
		m_This->InicializaMock();
	}
	return m_This;
}

Comodo* DAOComodo::RecuperarPorCodigo(uint16_t codigo)
{
	for(auto const& comodo: mockComodos) 
	{
		if(((Comodo*) comodo)->codigo == codigo)
			return (Comodo*) comodo;
	}

	return NULL;
}

std::vector<Comodo*> DAOComodo::GetComodos()
{
	return mockComodos;
}

void DAOComodo::InicializaMock()
{
	mockComodos.push_back(new Comodo
	{
		.codigo = 1,
		.nome = "Sala"
	});
	
	mockComodos.push_back(new Comodo
	{
		.codigo = 2,
		.nome = "Cozinha"
	});
}