#include "stdafx.h"
#include "Atributos.h"

Atributos::Atributos(int nivel)
{
	// atributos
	_vitalidad = 1;
	_fuerza = 1;
	_agilidad = 1;
	_destreza = 1;
	_inteligencia = 1;

	// Sistema de leveo
	_nivel = nivel;
	_experiencia = static_cast<int>((50 / 3) * (pow(_nivel +1, 3) - 6 * pow(_nivel +1, 2) + ((_nivel+1 * 17)) - 12));;
	_expSiguienteNivel = 0;
	_puntosAtributo = 0;

	actualizarNivel();
	actualizarEstadisticas(true);
}

Atributos::~Atributos()
{
}



const int Atributos::getHP()
{
	return _hp;
}

const int Atributos::getHPMax()
{
	return _hpMax;
}

const int Atributos::getExp()
{
	return _experiencia;
}

const int Atributos::getExpSiguienteNivel()
{
	return _expSiguienteNivel;
}

const int Atributos::getNivel()
{
	return _nivel;
}



void Atributos::perderVida(const int hp)
{
	_hp -= hp;

	if (_hp <= 0) _hp = 0;
}

void Atributos::ganarVida(const int hp)
{
	_hp += hp;

	if (_hp >= _hpMax) _hp = _hpMax;
}

void Atributos::perderExperiencia(const int experiencia)
{
	_experiencia += experiencia;

	if (_experiencia <  0) _experiencia = 0;
}

void Atributos::ganarExperiencia(const int experiencia)
{
	_experiencia += experiencia;

	actualizarNivel();
}

const bool Atributos::estaVivo() const
{
	if (_hp > 0) return true;
	else return false;
}

void Atributos::actualizarEstadisticas(const bool reset)
{
	_hpMax		= _vitalidad * 9 + _vitalidad + _fuerza / 5;
	_dmgMin		= _fuerza * 2 + _fuerza / 4; // TODO: agregar daño arma / agregar inteligencia (no es mala idea)
	_dmgMax		= _fuerza * 2 + _fuerza / 2; //TODO: agregar año arma
	_punteria	= _destreza * 4 + _destreza / 3;
	_defensa	= _agilidad * 2 + _agilidad / 4 + _fuerza / 5;
	_suerte		= _inteligencia * 2 + _inteligencia / 5;
	
	
	if (reset)
	{
		_hp = _hpMax;
	}
}



void Atributos::actualizarNivel()
{
	if (_experiencia >= _expSiguienteNivel) // TODO: podria ser un while
	{
		++_nivel;
		_experiencia -= _expSiguienteNivel;
		_expSiguienteNivel = static_cast<int>((50 / 3) * (pow(_nivel, 3) - 6 * pow(_nivel, 2) + (_nivel * 17) - 12));
		_puntosAtributo += 5;
	}
}

void Atributos::actualizar()
{
	actualizarNivel();
}

std::string Atributos::debug() const
{
	std::stringstream ss;
	ss << "Nivel: " << _nivel << "\n"
		<< "Exp: " << _experiencia << "\n"
		<< "Sig Lvl: " << _expSiguienteNivel << "\n"
		<< "Pts: " << _puntosAtributo << "\n";
	return ss.str();
}
