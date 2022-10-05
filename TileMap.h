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
		std::vector<std::vector<std::vector<Tile*> > > _mapa;
	public:
		TileMap(float tamanioCuadro, unsigned ancho, unsigned alto);
		virtual ~TileMap();

		void agregarTile(const unsigned x, const unsigned y, const unsigned z);
		void removerTile(const unsigned x, const unsigned y, const unsigned z);

		void actualizar();
		void renderizar(sf::RenderTarget& target);
};

#endif