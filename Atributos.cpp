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
	_experiencia = 0;
	_expSiguienteNivel = static_cast<unsigned>((50/3) * (pow(_nivel, 3) - 6 * pow(_nivel, 2) + (_nivel * 17) - 12));
	_puntosAtributo = 0;

	actualizarEstadisticas(true);
}

Atributos::~Atributos()
{
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

void Atributos::subirExp(const unsigned experiencia)
{
	_experiencia += experiencia;
	actualizarNivel();
}

void Atributos::actualizarNivel()
{
	if (_experiencia >= _expSiguienteNivel) // TODO: podria ser un while
	{
		++_nivel;
		_experiencia -= _expSiguienteNivel;
		_expSiguienteNivel = static_cast<unsigned>((50 / 3) * (pow(_nivel, 3) - 6 * pow(_nivel, 2) + (_nivel * 17) - 12));
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
