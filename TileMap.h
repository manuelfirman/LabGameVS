#ifndef TILEMAP_H
#define TILEMAP_H
#include "Tile.h"

class Tile;

class TileMap
{
	private:
		float _tamanioCuadroF;
		unsigned _tamanioCuadroU;
		unsigned _capas;
		sf::Vector2u _tamanioMax;
		std::vector<std::vector<std::vector<Tile> > > _mapa;
	public:
		TileMap();
		virtual ~TileMap();

		void actualizar();
		void renderizar(sf::RenderTarget& target);
};

#endif