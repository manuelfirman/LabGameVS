#include "stdafx.h" // precompilado
#include "TileMap.h"

void TileMap::limpiar()
{
	for (int x = 0; x < _tamanioMaxCuadros.x; x++)
	{
		for (int y = 0; y < _tamanioMaxCuadros.x; y++)
		{
			for (int z = 0; z < _Capas; z++)
			{
				for(int C = 0; C < _mapa[x][y][z].size(); C++)
				{
					delete _mapa[x][y][z][C]; // borra el anterior
					_mapa[x][y][z][C] = NULL; // habilita de nuevo
				}
				_mapa[x][y][z].clear();
			}
			_mapa[x][y].clear();
		}
		_mapa[x].clear();
	}
	_mapa.clear();

	//std::cout << _mapa.size() << "\n";
}

TileMap::TileMap(float tamanioCuadro, int ancho, int alto, std::string archivo_textura)
{
	_tamanioCuadroF = tamanioCuadro;
	_tamanioCuadroI = static_cast<int>(_tamanioCuadroF);
	_tamanioMaxCuadros.x = ancho;
	_tamanioMaxCuadros.y = alto;
	_tamanioMaxMundo.x = static_cast<float>(ancho) * tamanioCuadro;
	_tamanioMaxMundo.y = static_cast<float>(alto) * tamanioCuadro;
	_Capas = 1;
	_archivoTextura = archivo_textura;

	_desdeX = 0;
	_hastaX = 0;
	_desdeY = 0;
	_hastaY = 0;
	_capa = 0;

	_mapa.resize(_tamanioMaxCuadros.x, std::vector<std::vector<std::vector<Tile*> > >());
	for (int x = 0; x < _tamanioMaxCuadros.x; x++)
	{
		for (int y = 0; y < _tamanioMaxCuadros.y; y++)
		{
			_mapa[x].resize(_tamanioMaxCuadros.y, std::vector<std::vector<Tile*> >());
		
			for (int z = 0; z < _Capas; z++)
			{
				_mapa[x][y].resize(_Capas, std::vector<Tile*>());
			}
		}
	}
	
	if (!_texturaTile.loadFromFile(archivo_textura))
		std::cout << "ERROR:TILEMAP::NO SE PUDO CARGAR PLANTILLA TEXTURA::" << archivo_textura << "\n";

	_cajaColisiones.setSize(sf::Vector2f(tamanioCuadro, tamanioCuadro));
	_cajaColisiones.setFillColor(sf::Color(255, 0, 0, 50));
	_cajaColisiones.setOutlineColor(sf::Color::Red);
	_cajaColisiones.setOutlineThickness(1.f);
}

TileMap::~TileMap()
{
	limpiar();
}

const sf::Texture* TileMap::getTexturaTile() const
{
	return &_texturaTile;
}

const int TileMap::getTilesPorCuadro(const int x, const int y, const int capa) const
{
	if (x >= 0 && x < _mapa.size())
	{
		if (y >= 0 && y < _mapa[x].size())
		{
			if (capa >= 0 && capa < _mapa[x][y].size())
			{
				return _mapa[x][y][capa].size();
			}
		}
	}
	
	return -1;
}

void TileMap::agregarTile(const int x, const int y, const int z, const sf::IntRect& rect_textura, const bool& colision, const short& tipo)
{
	// Agrega un tile en la posicion del mouse si la matriz del mapa lo permite
	if ((x < _tamanioMaxCuadros.x) && (x >= 0) && 
		(y < _tamanioMaxCuadros.y) && (x >= 0) &&
		(z <= _Capas) && (z >= 0))
	{
		//if (_mapa[x][y][z] == NULL)
		//{
			// se puede agregar tile
			_mapa[x][y][z].push_back (new Tile(x, y, _tamanioCuadroF, _texturaTile, rect_textura, colision, tipo));
			std::cout << "DEBUG: TILE AGREGADO" << std::endl;
		//}
	}
}

void TileMap::removerTile(const int x, const int y, const int z)
{
	// Quita un tile en la posicion del mouse si la matriz del mapa lo permite
	if ((x < _tamanioMaxCuadros.x) && (x >= 0) &&
		(y < _tamanioMaxCuadros.y) && (x >= 0) &&
		(z <= _Capas) && (z >= 0))
	{
		if (!_mapa[x][y][z].empty())
		{
			// se puede quitar el tile
			delete _mapa[x][y][z][_mapa[x][y][z].size() - 1];
			_mapa[x][y][z].pop_back();

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
				Posicion cuadro x y capa
				Rect textura x y
				Colision
				Tipo
	*/

	std::ofstream archivoOut;
	archivoOut.open(nombre_archivo);
	if (archivoOut.is_open())
	{
		archivoOut << _tamanioMaxCuadros.x << " " << _tamanioMaxCuadros.y << "\n"
				<< _tamanioCuadroI << "\n"
				<< _Capas << "\n"
				<< _archivoTextura << "\n";

		for (int x = 0; x < _tamanioMaxCuadros.x; x++)
		{
			for (int y = 0; y < _tamanioMaxCuadros.y; y++)
			{
				for (int z = 0; z < _Capas; z++)
				{
					if(!_mapa[x][y][z].empty()) // si no esta vacio
					{
						for (size_t C = 0; C < _mapa[x][y][z].size(); C++)
						{
							archivoOut << x << " " << y << " " << z << " " << _mapa[x][y][z][C]->getTileString() << " "; // NO GUARDAR EL ULTIMO ESPACIO

						}
					}
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
	std::ifstream archivoIn;
	archivoIn.open(nombre_archivo);

	if (archivoIn.is_open())
	{
		// Inicializar para no tener basura
		sf::Vector2u tamanio;
		int tamanioCuadro = 0;
		int capas = 0;
		std::string archivoTextura = "";
		int x = 0;
		int y = 0;
		int z = 0;
		int trX = 0;
		int trY = 0;
		bool colision = false;
		short tipo = 0;

		// Basicos
		archivoIn >> tamanio.x >> tamanio.y >> tamanioCuadro >> capas >> archivoTextura;
		
		// Tiles
		_tamanioCuadroF = static_cast<float>(tamanioCuadro);
		_tamanioCuadroI = tamanioCuadro;
		_tamanioMaxCuadros.x = tamanio.x;
		_tamanioMaxCuadros.y = tamanio.y;
		_Capas = capas;
		_archivoTextura = archivoTextura;

		limpiar();

		_mapa.resize(_tamanioMaxCuadros.x, std::vector< std::vector< std::vector<Tile*> > >());
		for (int x = 0; x < _tamanioMaxCuadros.x; x++)
		{
			for (int y = 0; y < _tamanioMaxCuadros.y; y++)
			{
				_mapa[x].resize(_tamanioMaxCuadros.y, std::vector< std::vector<Tile*> >());

				for (int z = 0; z < _Capas; z++)
				{
					_mapa[x][y].resize(_Capas, std::vector<Tile*>());
				}
			}
		}

		if (!_texturaTile.loadFromFile(_archivoTextura))
			std::cout << "ERROR:TILEMAP::NO SE PUDO CARGAR PLANTILLA TEXTURA::" << _archivoTextura << "\n";

		// Carga todos los tiles
		while (archivoIn >> x >> y >> z >> trX >> trY >> colision >> tipo)
		{
			_mapa[x][y][z].push_back(new Tile(
				x, y, 
				_tamanioCuadroF, 
				_texturaTile, 
				sf::IntRect(trX, trY, _tamanioCuadroI, _tamanioCuadroI), 
				colision, 
				tipo));
		}
	}
	else
	{
		std::cout << "ERROR::TILEMAP::NO SE PUDO CARGAR DESDE ARCHIVO::" << nombre_archivo << "\n";
	}

	archivoIn.close();
}

void TileMap::checkColision(Entidades* entidad, const float& DT)
{
	// LIMITES MAPA
		// Laterales
	if (entidad->getPosicionSprite().x < 0.f)
	{
		//entidad->detenerX();
		entidad->setPosicion(0.f, entidad->getPosicionSprite().y);
	}
	else if (entidad->getPosicionSprite().x + entidad->getLimites().width > _tamanioMaxMundo.x)
	{
		//entidad->detenerX();
		entidad->setPosicion(_tamanioMaxMundo.x - entidad->getLimites().width, entidad->getPosicionSprite().y);
	}
		// Superior / Inferior
	if (entidad->getPosicionSprite().y < 0.f)
	{
		entidad->detenerY();
		entidad->setPosicion(entidad->getPosicionSprite().x, 0.f);
	}
	else if (entidad->getPosicionSprite().y + entidad->getLimites().height > _tamanioMaxMundo.y)
	{
		entidad->detenerY();
		entidad->setPosicion(entidad->getPosicionSprite().x, _tamanioMaxMundo.y - entidad->getLimites().height);
	}


	_capa = 0;

	_desdeX = entidad->getCuadroActual(_tamanioCuadroI).x - 1;
	if (_desdeX < 0)
		_desdeX = 0;
	else if (_desdeX > _tamanioMaxCuadros.x)
		_desdeX = _tamanioMaxCuadros.x;

	_hastaX = entidad->getCuadroActual(_tamanioCuadroI).x + 3;
	if (_hastaX < 0)
		_hastaX = 0;
	else if (_hastaX > _tamanioMaxCuadros.x)
		_hastaX = _tamanioMaxCuadros.x;

	_desdeY = entidad->getCuadroActual(_tamanioCuadroI).y - 1;
	if (_desdeY < 0)
		_desdeY = 0;
	else if (_desdeY > _tamanioMaxCuadros.y)
		_desdeY = _tamanioMaxCuadros.y;

	_hastaY = entidad->getCuadroActual(_tamanioCuadroI).y + 3;
	if (_hastaY < 0)
		_hastaY = 0;
	else if (_hastaY > _tamanioMaxCuadros.y)
		_hastaY = _tamanioMaxCuadros.y;


	for (int x = _desdeX; x < _hastaX; x++)
	{
		for (int y = _desdeY; y < _hastaY; y++)
		{
			for(int C = 0; C < _mapa[x][y][_capa].size(); C++)
			{
				sf::FloatRect limitesJugador = entidad->getLimites();
				sf::FloatRect limitesMuros = _mapa[x][y][_capa][C]->getLimites();
				sf::FloatRect limitesPosSiguiente = entidad->getLimitesPosSiguiente(DT);

				if (this->_mapa[x][y][_capa][C]->getColision() &&
					this->_mapa[x][y][_capa][C]->interseccion(limitesPosSiguiente)
					)
				{
					//Bottom collision
					if (limitesJugador.top < limitesMuros.top
						&& limitesJugador.top + limitesJugador.height < limitesMuros.top + limitesMuros.height
						&& limitesJugador.left < limitesMuros.left + limitesMuros.width
						&& limitesJugador.left + limitesJugador.width > limitesMuros.left
						)
					{
						entidad->detenerY();
						entidad->setPosicion(limitesJugador.left, limitesMuros.top - limitesJugador.height);
					}

					//Top collision
					else if (limitesJugador.top > limitesMuros.top
						&& limitesJugador.top + limitesJugador.height > limitesMuros.top + limitesMuros.height
						&& limitesJugador.left < limitesMuros.left + limitesMuros.width
						&& limitesJugador.left + limitesJugador.width > limitesMuros.left
						)
					{
						entidad->detenerY();
						entidad->setPosicion(limitesJugador.left, limitesMuros.top + limitesMuros.height);
					}

					//Right collision
					if (limitesJugador.left < limitesMuros.left
						&& limitesJugador.left + limitesJugador.width < limitesMuros.left + limitesMuros.width
						&& limitesJugador.top < limitesMuros.top + limitesMuros.height
						&& limitesJugador.top + limitesJugador.height > limitesMuros.top
						)
					{
						entidad->detenerX();
						entidad->setPosicion(limitesMuros.left - limitesJugador.width, limitesJugador.top);
					}

					//Left collision
					else if (limitesJugador.left > limitesMuros.left
						&& limitesJugador.left + limitesJugador.width > limitesMuros.left + limitesMuros.width
						&& limitesJugador.top < limitesMuros.top + limitesMuros.height
						&& limitesJugador.top + limitesJugador.height > limitesMuros.top
						)
					{
						entidad->detenerX();
						entidad->setPosicion(limitesMuros.left + limitesMuros.width, limitesJugador.top);
					}
				}
			}
		}
	}
}

void TileMap::actualizar()
{

}

void TileMap::renderizar(sf::RenderTarget& target, const sf::Vector2i posicionCuadro) // se puede enviar cualquier posicion (player, vista, etc)
{
	// TILES
	_capa = 0;

	_desdeX = posicionCuadro.x - 4;
	if (_desdeX < 0)
		_desdeX = 0;
	else if (_desdeX > _tamanioMaxCuadros.x)
		_desdeX = _tamanioMaxCuadros.x;

	_hastaX = posicionCuadro.x + 5;
	if (_hastaX < 0)
		_hastaX = 0;
	else if (_hastaX > _tamanioMaxCuadros.x)
		_hastaX = _tamanioMaxCuadros.x;

	_desdeY = posicionCuadro.y - 3;
	if (_desdeY < 0)
		_desdeY = 0;
	else if (_desdeY > _tamanioMaxCuadros.y)
		_desdeY = _tamanioMaxCuadros.y;

	_hastaY = posicionCuadro.y + 5;
	if (_hastaY < 0)
		_hastaY = 0;
	else if (_hastaY > _tamanioMaxCuadros.y)
		_hastaY = _tamanioMaxCuadros.y;


	for (int x = _desdeX; x < _hastaX; x++)
	{
		for (int y = _desdeY; y < _hastaY; y++)
		{
			for (int C = 0; C < _mapa[x][y][_capa].size(); C++)
			{	
				// Orden de renderizado
				if (_mapa[x][y][_capa][C]->getTipoTile() == TipoTile::TOP)
				{
					_pilaRenderDiferida.push(_mapa[x][y][_capa][C]);
				}
				else
				{
					_mapa[x][y][_capa][C]->renderizar(target);
				}

				// Colision con tiles
				if (_mapa[x][y][_capa][C]->getColision())
				{
					_cajaColisiones.setPosition(_mapa[x][y][_capa][C]->getPosicionTile());
					target.draw(_cajaColisiones);
				}
			}
		}
	}
}

void TileMap::renderizacionDiferida(sf::RenderTarget& target)
{
	while (!_pilaRenderDiferida.empty())
	{
		_pilaRenderDiferida.top()->renderizar(target); // renderiza y lo saca de la pila
		_pilaRenderDiferida.pop();
	}
}
