#ifndef TILEMAP_H
#define TILEMAP_H
#include "Tile.h"

class TileMap
{
	private:
		unsigned _capas;
		unsigned _tamanioCuadroU;
		sf::Vector2u _tamanioMax;
		std::vector<std::vector<std::vector<Tile> > > _mapa;
	public:
		TileMap();
		virtual ~TileMap();
};

#endif