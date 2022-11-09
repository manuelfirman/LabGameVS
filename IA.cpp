#include "stdafx.h"
#include "IA.h"

IA::IA(Entidades& jugador, Entidades& entidad) : _jugador(jugador), _entidad(entidad)
{
}

IA::~IA()
{
}

void IA::seguir(const float& DT)
{
	sf::Vector2f movimiento;
	movimiento.x = _jugador.getPosicionSprite().x - _entidad.getPosicionSprite().x;
	movimiento.y = _jugador.getPosicionSprite().y - _entidad.getPosicionSprite().y;

	// TODO: setear agro de los minions a traves de un condicional con la longitud
	float longitud = static_cast<float>(sqrt(pow(movimiento.x, 2) + pow(movimiento.y, 2))); // mov_x^2 + mov_y^ (entre el jugador y la entidad)

	movimiento /= longitud;

	if (_jugador.getPosicionSprite().x != _entidad.getPosicionSprite().x)
	{
		_entidad.mover(movimiento.x, movimiento.y, DT);
	}
}