#include "stdafx.h"
#include "SpawnerEnemigos.h"



SpawnerEnemigos::SpawnerEnemigos(int cuadro_x, int cuadro_y, float tamanioCuadroF, sf::Texture& textura, const sf::IntRect& rect_textura,
	float tamanio_cuadro, int tipo_enemigo, int cantidad_enemigos, int tiempo_spawn, float distancia_max)
	: Tile(cuadro_x, cuadro_y, tamanioCuadroF, textura, rect_textura, false, tipo_tile::SPAWNERENEMIGO)
{
	_tipoEnemigo = tipo_enemigo;
	_cantidadEnemigos = cantidad_enemigos;
	_tiempoSpawn = tiempo_spawn;
	_distanciaMax = distancia_max;
}

SpawnerEnemigos::~SpawnerEnemigos()
{
}

void SpawnerEnemigos::actualizar()
{
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
