#include "stdafx.h" // precompilado
#include "TileMap.h"

TileMap::TileMap(float tamanioCuadro, unsigned ancho, unsigned alto, std::string archivo_textura)
{
	_tamanioCuadroF = tamanioCuadro;
	_tamanioCuadroU = static_cast<unsigned>(_tamanioCuadroF);
	_tamanioMax.x = ancho;
	_tamanioMax.y = alto;
	_capas = 1;
	_archivoTextura = archivo_textura;

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
	
	if (!_texturaTile.loadFromFile(archivo_textura))
		std::cout << "ERROR:TILEMAP::NO SE PUDO CARGAR PLANTILLA TEXTURA::" << archivo_textura << "\n";
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

const sf::Texture* TileMap::getTexturaTile() const
{
	return &_texturaTile;
}

void TileMap::agregarTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& rect_textura)
{
	// Agrega un tile en la posicion del mouse si la matriz del mapa lo permite
	if ((x < _tamanioMax.x) && (x >= 0) && 
		(y < _tamanioMax.y) && (x >= 0) &&
		(z <= _capas) && (z >= 0))
	{
		if (_mapa[x][y][z] == NULL)
		{
			// se puede agregar tile
			_mapa[x][y][z] = new Tile(x * _tamanioCuadroF, y * _tamanioCuadroF, _tamanioCuadroF, _texturaTile, rect_textura);
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


void TileMap::guardarEnArchivo(const std::string nombre_archivo)
{
	/*
	Guardar el tileMap en un archivo de texto
		Formato:
			Basico:
				Tamaño x y
				Tamaño cuadro
				Capas
				Archivo textura

			Tiles:
				Posicion cuadro x y
				Rect textura x y
	*/

	std::ofstream archivoOut;
	archivoOut.open(nombre_archivo);
	if (archivoOut.is_open())
	{
		archivoOut << _tamanioMax.x << " " << _tamanioMax.y << "\n"
				<< _tamanioCuadroU << "\n"
				<< _capas << "\n"
				<< _archivoTextura << "\n";

		for (size_t x = 0; x < _tamanioMax.x; x++)
		{
			for (size_t y = 0; y < _tamanioMax.x; y++)
			{
				for (size_t z = 0; z < _capas; z++)
				{
					archivoOut << 1 << 2 << 3 << 5 << " ";
					//archivoOut << _mapa[x][y][z];
				}
			}
		}
	}
	else
	{
		std::cout << "ERROR::TILEMAP::NO SE PUDO GUARDAR EN ARCHIVO::" << nombre_archivo << "\n";
	}

	archivoOut.close();

}

void TileMap::cargarDesdeArchivo(const std::string nombre_archivo)
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
			for (auto* z : y) // for para las capas - pasa por Y y nos da el tile
			{
				if(z != nullptr) // no renderiza vacios
					z->renderizar(target);
			}
		}
	}
	// No se renderiza nada que no este dentro de la ventana (cuadricula _mapa)
}