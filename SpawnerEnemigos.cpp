#include "stdafx.h"
#include "SpawnerEnemigos.h"



SpawnerEnemigos::SpawnerEnemigos(sf::Vector2i posicion, int tipo, int cantidad, int tiempo_spawn, float distancia_max)
{
	_posicionCuadro = posicion;
	_tipo = tipo;
	_cantidad = cantidad;
	_tiempoSpawn = tiempo_spawn;
	_distanciaMax = distancia_max;
}

SpawnerEnemigos::~SpawnerEnemigos()
{
}

void SpawnerEnemigos::spawn()
{
}

void SpawnerEnemigos::limpiar()
{
}

void SpawnerEnemigos::actualizar(const float& DT)
{
}

void SpawnerEnemigos::renderizar(sf::RenderTarget& target)
{

}
