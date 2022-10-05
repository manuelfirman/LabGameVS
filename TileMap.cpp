#include "stdafx.h" // precompilado
#include "TileMap.h"

TileMap::TileMap(float tamanioCuadro, unsigned ancho, unsigned alto)
{
	_tamanioCuadroF = tamanioCuadro;
	_tamanioCuadroU = static_cast<unsigned>(_tamanioCuadroF);
	_tamanioMax.x = ancho;
	_tamanioMax.y = alto;
	_capas = 1;

	_mapa.resize(_tamanioMax.x, std::vector<std::vector<Tile*>>()); // revisar resize

	for (size_t x = 0; x < _tamanioMax.x; x++) // pushea Tiles vacios
	{
		for (size_t y = 0; y < _tamanioMax.x; y++)
		{
			_mapa[x].resize(_tamanioMax.y, std::vector<Tile*>());
		
			for (size_t z = 0; z < _capas; z++)
			{
				_mapa[x][y].resize(_capas, NULL);
			}
		}
			

	}
}

TileMap::~TileMap()
{
	for (size_t x = 0; x < _tamanioMax.x; x++)
	{
		for (size_t y = 0; y < _tamanioMax.x; y++)
		{
			for (size_t z = 0; z < _capas; z++)
			{
				delete _mapa[x][y][z];
			}
		}


	}
}

void TileMap::agregarTile(const unsigned x, const unsigned y, const unsigned z)
{
	// Agrega un tile en la posicion del mouse si la matriz del mapa lo permite
	if ((x < _tamanioMax.x) && (x >= 0) && 
		(y < _tamanioMax.y) && (x >= 0) && 
		(z <= _capas) && (z >= 0))
	{
		if (_mapa[x][y][z] == NULL)
		{
			// se puede agregar tile
			_mapa[x][y][z] = new Tile(x * _tamanioCuadroF, y * _tamanioCuadroF, _tamanioCuadroF);
			std::cout << "DEBUG: TILE AGREGADO" << std::endl;
		}
	}
}

void TileMap::removerTile(const unsigned x, const unsigned y, const unsigned z)
{
	// Quita un tile en la posicion del mouse si la matriz del mapa lo permite
	if ((x < _tamanioMax.x) && (x >= 0) &&
		(y < _tamanioMax.y) && (x >= 0) &&
		(z <= _capas) && (z >= 0))
	{
		if (_mapa[x][y][z] != NULL)
		{
			// se puede quitar el tile
			delete _mapa[x][y][z];
			_mapa[x][y][z] = NULL;

			std::cout << "DEBUG: TILE REMOVIDO" << std::endl;
		}
	}

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
			for (auto* z : y) // for para las capas - pasa por Y y nos da el tile
			{
				if(z != nullptr) // no renderiza vacios
					z->renderizar(target);
			}
		}
	}

	// No se renderiza nada que no este dentro de la ventana (cuadricula _mapa)
}
