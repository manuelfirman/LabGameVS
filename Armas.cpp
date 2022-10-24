#include "stdafx.h"
#include "Armas.h"

void Armas::iniciarVariables()
{
	_rango = 10;
}

Armas::Armas(unsigned valor, std::string ruta_textura)
	: Items(valor)
{
	if (!_texturaArma.loadFromFile(ruta_textura))
		std::cout << "ERROR::ARMAMELEE::NO SE PUDO CARGAR LA TEXTURA: " << ruta_textura << std::endl;
}

Armas::~Armas()
{
}

const unsigned& Armas::getRango() const
{
	return _rango;
}
