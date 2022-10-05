#include "stdafx.h" // precompilado
#include "TileMap.h"

TileMap::TileMap()
{
	_tamanioCuadroU = 50;
	_tamanioMax.x = 5000;
	_tamanioMax.y = 5000;
	_capas = 5;

	// pushea Tiles vacios
	for (size_t x = 0; x < _tamanioMax.x; x++) 
	{
		_mapa.push_back(std::vector<std::vector<Tile>>());
		
		for (size_t y = 0; y < _tamanioMax.x; y++)
		{
			_mapa[x].push_back(std::vector<Tile>()); 
			
			for (size_t z = 0; z < _capas; z++)
			{
				_mapa[x][y].push_back(Tile());
			}
		}
			

	}
}

TileMap::~TileMap()
{
}
