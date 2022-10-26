#include "stdafx.h"
#include "ArmaRango.h"

ArmaRango::ArmaRango(int nivel, unsigned valor, std::string ruta_textura)
	: Armas(nivel, valor, ruta_textura)
{
	//std::cout << "Test arma rango" << std::endl;
	_tipo = tipo_item::ARMA_RANGO;
}

ArmaRango::~ArmaRango()
{
}
