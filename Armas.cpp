#include "stdafx.h"
#include "Armas.h"

void Armas::iniciarVariables()
{
	_rango = 50;
	_dmgMin = 1;
	_dmgMax = 3;

	_timerAtaque.restart();
	_timerAtaqueMax = 400;
}

Armas::Armas(int nivel, unsigned valor, std::string ruta_textura)
	: Items(nivel, valor)
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

const int Armas::getDMG() const
{
	//return rand() % (_dmgMax - _dmgMin) + _dmgMin;
	return _dmgMin + rand() % (_dmgMax-_dmgMin+1);
}

const unsigned& Armas::getRango() const
{
	return _rango;
}

const bool Armas::getTimerAtaque()
{
	//std::cout << _timerAtaque.getElapsedTime().asMicroseconds() << std::endl;
	if (_timerAtaque.getElapsedTime().asMilliseconds() >= _timerAtaqueMax)
	{
		_timerAtaque.restart();
		return true;
	}

	return false;
}