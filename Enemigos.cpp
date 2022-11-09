#include "stdafx.h"
#include "Enemigos.h"

void Enemigos::iniciarVariables()
{
	_experiencia = 5;
	_timerDmgMax = 1000;
	_timerAtaqueMax = 1000;
	_rango = 20;
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

const unsigned& Enemigos::getRango() const
{
	return _rango;
}

const float Enemigos::getDistanciaSkill(const sf::Sprite& skill) const
{
	return static_cast<float>(sqrt(pow((getCentro().x - skill.getPosition().x), 2) + pow((getCentro().y - skill.getPosition().y), 2)));
}

void Enemigos::resetTimerAtaque()
{
	_timerAtaque.restart();
}

const bool Enemigos::getAtaqueTerminado() const
{
	if (_timerAtaque.getElapsedTime().asMilliseconds() >= _timerAtaqueMax) return true;

	else return false;
}

void Enemigos::resetTimerDmg()
{
	_timerDmg.restart();
}

const bool Enemigos::getDmgTerminado() const
{
	if (_timerDmg.getElapsedTime().asMilliseconds() >= _timerDmgMax) return true;
	
	else return false;
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