#include "stdafx.h"
#include "SpawnerEnemigos.h"



SpawnerEnemigos::SpawnerEnemigos(int cuadro_x, int cuadro_y, float tamanioCuadroF, sf::Texture& textura, const sf::IntRect& rect_textura,
	int tipo_enemigo, int cantidad_enemigos, sf::Int32 tiempo_spawn, float distancia_max)
	: Tile(tipo_tile::SPAWNERENEMIGO, cuadro_x, cuadro_y, tamanioCuadroF, textura, rect_textura, false)
{
	_spawneado = false;
	_tipoEnemigo = tipo_enemigo;
	_cantidadEnemigos = cantidad_enemigos;
	_distanciaMax = distancia_max;
	_timerSpawn.restart();
	_tiempoSpawn = tiempo_spawn;
}

SpawnerEnemigos::~SpawnerEnemigos()
{
}

void SpawnerEnemigos::setSpawn(const bool spawneado)
{
	_spawneado = spawneado;
	_timerSpawn.restart(); // reseteo el timer
}

const bool SpawnerEnemigos::puedeSpawnear()
{
	if (_timerSpawn.getElapsedTime().asSeconds() >= _tiempoSpawn) return true;
	
	return false;
}

const bool& SpawnerEnemigos::getSpawn()
{
	return _spawneado;
}

const std::string SpawnerEnemigos::getTileString() const
{
	std::stringstream ss;
	// x, y, z, tipo, rect x, rect y, tipo enemigo, cantidad, tiempo spawn, distancia max
	ss << _tipoTile << " " << _tile.getTextureRect().left << " " << _tile.getTextureRect().top << " " << _tipoEnemigo << " " << _cantidadEnemigos << " " << _tiempoSpawn << " " << _distanciaMax;

	return ss.str();
}

void SpawnerEnemigos::actualizar()
{
	if (puedeSpawnear())
		_spawneado = false;
}

void SpawnerEnemigos::renderizar(sf::RenderTarget& target, const sf::Vector2f posicionJugador = sf::Vector2f(), sf::Shader* sombra = NULL)
{
	if (sombra)
	{
		sombra->setUniform("tieneTextura", true);
		sombra->setUniform("luz", posicionJugador);

		target.draw(testShape, sombra);
	}
	else
	{
		target.draw(testShape);
	}
}
