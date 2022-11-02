#include "stdafx.h"
#include "Atributos.h"
Atributos::Atributos()
{
	_nivel = 0;
	_vitalidad = 0;
	_fuerza = 0;
	_agilidad = 0;
	_destreza = 0;
	_inteligencia = 0;
	_experiencia = 0;
	_expSiguienteNivel = static_cast<int>((50.f / 3) * (pow(_nivel + 1, 3) - 6 * pow(_nivel + 1, 2) + ((_nivel + 1 * 17)) - 12));
	_hp = 0;
	_hpMax = 0;
	_dmgMax = 0;
	_dmgMin = 0;
	_defensa = 0;
	_puntosAtributo = 0;
}

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
	_experiencia = 0;
	_expSiguienteNivel = static_cast<int>(std::pow(_nivel, 2)) + _nivel * 10 + _nivel * 2;
	_puntosAtributo = 0;

	actualizarEstadisticas(true);
}

Atributos::Atributos(int nivel, int experiencia, int hp, int vitalidad, int fuerza, int agilidad, int destreza, int inteligencia)
{
	_nivel = nivel;
	_experiencia = experiencia;
	_expSiguienteNivel = static_cast<int>(std::pow(_nivel, 2)) + _nivel * 10 + _nivel * 2;
	_hp = hp;
	_vitalidad = vitalidad;
	_fuerza = fuerza;
	_agilidad = agilidad;
	_destreza = destreza;
	_inteligencia = inteligencia;
	_puntosAtributo = 0;

	actualizarNivel();
	actualizarEstadisticas(false);
}

Atributos::~Atributos()
{
}

void Atributos::setNivel(int nivel)
{
	_nivel = nivel;
}

void Atributos::setExperiencia(int experiencia)
{
	_experiencia = experiencia;
}

void Atributos::setHP(int hp)
{
	_hp = hp;
}

void Atributos::setVitalidad(int vitalidad)
{
	_vitalidad = vitalidad;
}

void Atributos::setFuerza(int fuerza)
{
	_fuerza = fuerza;
}

void Atributos::setAgilidad(int agilidad)
{
	_agilidad = agilidad;
}

void Atributos::setDestreza(int destreza)
{
	_destreza = destreza;
}

void Atributos::setInteligencia(int inteligencia)
{
	_inteligencia = inteligencia;
}

void Atributos::setPuntosAtributo(int puntos)
{
	_puntosAtributo = puntos;
}


const int Atributos::getDmg()
{
	return _dmgMin + rand() % (_dmgMax - _dmgMin + 1);
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

const int Atributos::getVitalidad()
{
	return _vitalidad;
}

const int Atributos::getFuerza()
{
	return _fuerza;
}

const int Atributos::getAgilidad()
{
	return _agilidad;
}

const int Atributos::getDestreza()
{
	return _destreza;
}

const int Atributos::getInteligencia()
{
	return _inteligencia;
}

const int Atributos::getPuntosAtributo()
{
	return _puntosAtributo;
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
	_hpMax		= _vitalidad * 9 + _vitalidad + _fuerza / 5 + _inteligencia / 5 + _nivel / 2;
	_dmgMin		= _fuerza * 2 + _fuerza / 4 + _inteligencia / 5; // TODO: agregar daño arma / agregar inteligencia (no es mala idea)
	_dmgMax		= _fuerza * 2 + _fuerza / 2 + _inteligencia / 5; //TODO: agregar año arma
	_defensa	= _agilidad * 2 + _agilidad / 4 + _fuerza / 5 + _inteligencia / 5;;
	
	
	if (reset)
	{
		_hp = _hpMax;
	}
}



void Atributos::actualizarNivel()
{
	if (_experiencia >= _expSiguienteNivel) // TODO: podria ser un while
	{
		_nivel++;
		_experiencia = 0;
		_expSiguienteNivel = static_cast<int>(std::pow(_nivel, 2)) + _nivel * 10 + _nivel * 2;
		_puntosAtributo += 1;
		actualizarEstadisticas(true);
	}
}

void Atributos::actualizar()
{
	actualizarNivel();
	actualizarEstadisticas(false);
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
