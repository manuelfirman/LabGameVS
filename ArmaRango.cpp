#include "stdafx.h"
#include "ArmaRango.h"

ArmaRango::ArmaRango(unsigned valor, std::string ruta_textura)
	: Armas(valor, ruta_textura)
{
	//std::cout << "Test arma rango" << std::endl;
	_tipo = tipo_item::ARMA_RANGO;
}

ArmaRango::~ArmaRango()
{
}
