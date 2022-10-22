#ifndef SPAWNERENEMIGOS_H
#define SPAWNERENEMIGOS_H

#include "Tile.h"

class SpawnerEnemigos : public Tile
{
	private:

		sf::RectangleShape testShape;
		sf::Vector2i _posicionCuadro;
		int _tipoEnemigo;
		int _cantidadEnemigos;
		int _tiempoSpawn;
		float _distanciaMax;


	public:
		SpawnerEnemigos(int cuadro_x, int cuadro_y, float tamanioCuadroF, sf::Texture& textura, const sf::IntRect& rect_textura,
			float tamanio_cuadro, int tipo_enemigo, int cantidad_enemigos, int tiempo_spawn, float distancia_max);
		virtual ~SpawnerEnemigos();

		void actualizar();
		void renderizar(sf::RenderTarget& target, const sf::Vector2f posicionJugador, sf::Shader* sombra);

};

#endif // !SPAWNERENEMIGOS_H
