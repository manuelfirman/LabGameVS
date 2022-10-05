#include "stdafx.h" // precompilado
#include "TileMap.h"

TileMap::TileMap()
{
	_tamanioCuadroF = 100.f;
	_tamanioCuadroU = static_cast<unsigned>(_tamanioCuadroF);
	_tamanioMax.x = 10;
	_tamanioMax.y = 10;
	_capas = 1;

	_mapa.resize(_tamanioMax.x); // revisar resize

	// pushea Tiles vacios
	for (size_t x = 0; x < _tamanioMax.x; x++) 
	{
		_mapa.push_back(std::vector<std::vector<Tile>>());
		
		for (size_t y = 0; y < _tamanioMax.x; y++)
		{
			_mapa[x].resize(_tamanioMax.y);
			_mapa[x].push_back(std::vector<Tile>()); 
			
			for (size_t z = 0; z < _capas; z++)
			{
				_mapa[x][y].resize(_capas);
				_mapa[x][y].push_back(Tile(x * _tamanioCuadroF, y * _tamanioCuadroF, _tamanioCuadroF));
			}
		}
			

	}
}

TileMap::~TileMap()
{
}

void TileMap::actualizar()
{
}

void TileMap::renderizar(sf::RenderTarget& target)
{

	for (auto& x : _mapa)
	{
		for(auto &y : x) // x es una matriz
		{
			for (auto& z : y) // for para las capas - pasa por Y y nos da el tile
			{
				z.renderizar(target);
			}
		}
	}

	// No se renderiza nada que no este dentro de la ventana (cuadricula _mapa)
}
