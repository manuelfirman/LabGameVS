#include "stdafx.h"
#include "Armas.h"

void Armas::iniciarVariables()
{
	_rango = 10;
	_dmgMin = 0;
	_dmgMax = 1;
}

Armas::Armas(unsigned valor, std::string ruta_textura)
	: Items(valor)
{
	this->iniciarVariables();
	if (!_texturaArma.loadFromFile(ruta_textura))
		std::cout << "ERROR::ARMAMELEE::NO SE PUDO CARGAR LA TEXTURA: " << ruta_textura << std::endl;
}

Armas::~Armas()
{
}

const int& Armas::getDmgMin() const
{
	return _dmgMin;
}
const int& Armas::getDmgMax() const
{
	return _dmgMax;
}

const unsigned& Armas::getRango() const
{
	return _rango;
}
