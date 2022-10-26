#include "stdafx.h"
#include "Enemigos.h"

void Enemigos::iniciarVariables()
{
	_experiencia = 5;
}


void Enemigos::iniciarAnimaciones()
{

}

Enemigos::Enemigos(SpawnerEnemigos& tile_spawner) : _spawner(tile_spawner)
{
	this->iniciarVariables();
	this->iniciarAnimaciones();
}

Enemigos::~Enemigos()
{
}

SpawnerEnemigos& Enemigos::getTileSpawner()
{
	return _spawner;
}

void Enemigos::generarAtributos(const int nivel)
{
	_experiencia = nivel * 7;
	// dmg min y max
	// hp
	// etc
}


const int& Enemigos::getExperiencia() const
{
	return _experiencia;
}

const bool Enemigos::estaVivo() const
{
	if (_atributos)
	{
		return _atributos->estaVivo();
	}

	return false;
}

void Enemigos::perderVida(const int hp)
{
	if (_atributos)
	{
		_atributos->perderVida(hp);
	}
}


const Atributos* Enemigos::getAtributos() const
{
	if (_atributos)
	{
		return _atributos;
	}
	else
	{
		std::cout << "ERROR::ENEMIGOS::NO SE PUDO INICIALIZAR EL COMPONENTE DE ATRIBUTOS" << std::endl;
		return nullptr;
	}
}