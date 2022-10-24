#include "stdafx.h" // precompilado
#include "TileMap.h"

void TileMap::limpiar()
{
	if (!_mapa.empty())
	{
		for (int x = 0; x < _mapa.size(); x++)
		{
			for (int y = 0; y < _mapa[x].size(); y++)
			{
				for (int z = 0; z < _mapa[x][y].size(); z++)
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
	}

	//std::cout << _mapa.size() << "\n";
}

TileMap::TileMap(float tamanioCuadro, int ancho, int alto, std::string archivo_textura)
{
	_archivoTextura = archivo_textura;
	_tamanioCuadroF = tamanioCuadro;
	_tamanioCuadroI = static_cast<int>(_tamanioCuadroF);
	_tamanioMaxCuadros.x = ancho;
	_tamanioMaxCuadros.y = alto;
	_tamanioMaxMundo.x = static_cast<float>(ancho) * tamanioCuadro;
	_tamanioMaxMundo.y = static_cast<float>(alto) * tamanioCuadro;
	_Capas = 1;

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

TileMap::TileMap(const std::string archivo_textura)
{
	_desdeX = 0;
	_hastaX = 0;
	_desdeY = 0;
	_hastaY = 0;
	_capa = 0;

	cargarDesdeArchivo(archivo_textura);

	_cajaColisiones.setSize(sf::Vector2f(_tamanioCuadroF, _tamanioCuadroF));
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
	if (x >= 0 && x < static_cast<int>(_mapa.size()))
	{
		if (y >= 0 && y < static_cast<int>(_mapa[x].size()))
		{
			if (capa >= 0 && capa < static_cast<int>(_mapa[x][y].size()))
			{
				return static_cast<int>(_mapa[x][y][capa].size());
			}
		}
	}
	
	return -1;
}

const sf::Vector2f& TileMap::getTamanioMax() const
{
	return _tamanioMaxMundo;
}

const sf::Vector2i& TileMap::getTamanioMaxCuadros() const
{
	return _tamanioMaxCuadros;
}

const bool TileMap::tileVacio(const int x, const int y, const int z) const
{
	if(x >= 0 && x <= _tamanioMaxMundo.x && y >= 0 && y <= _tamanioMaxMundo.y && z >= 0 && z <= _Capas)
		return _mapa[x][z][z].empty();

	return false;
}

void TileMap::agregarTile(const int x, const int y, const int z, const sf::IntRect& rect_textura, const bool& colision, const short& tipo)
{
	// Agrega un tile en la posicion del mouse si la matriz del mapa lo permite
	if ((x < _tamanioMaxCuadros.x) && (x >= 0) && (y < _tamanioMaxCuadros.y) && (x >= 0) && (z <= _Capas) && (z >= 0))
	{
		_mapa[x][y][z].push_back (new TileNormal(tipo, x, y, _tamanioCuadroF, _texturaTile, rect_textura, colision));
	}
}

void TileMap::agregarTile(const int x, const int y, const int z, const sf::IntRect& rect_textura, const int tipo_enemigo, const int cantidad_enemigos, const int tiempo_spawn, const int distancia_max)
{
	if ((x < _tamanioMaxCuadros.x) && (x >= 0) && (y < _tamanioMaxCuadros.y) && (x >= 0) && (z <= _Capas) && (z >= 0))
	{
		_mapa[x][y][z].push_back(new SpawnerEnemigos(x, y, _tamanioCuadroF, _texturaTile, rect_textura, tipo_enemigo, cantidad_enemigos, tiempo_spawn, distancia_max));
	}
}

void TileMap::removerTile(const int x, const int y, const int z, const int tipo)
{
	// Quita un tile en la posicion del mouse si la matriz del mapa lo permite
	
	if ((x < _tamanioMaxCuadros.x) && (x >= 0) &&
		(y < _tamanioMaxCuadros.y) && (x >= 0) &&
		(z <= _Capas) && (z >= 0))
	{
		if (!_mapa[x][y][z].empty())
		{
			// se puede quitar el tile
			if (tipo >= 0)
			{
				if(_mapa[x][y][z].back()->getTipoTile() == tipo)
				{
					delete _mapa[x][y][z][_mapa[x][y][z].size() - 1];
					_mapa[x][y][z].pop_back();
				}
			}
			else
			{
				delete _mapa[x][y][z][_mapa[x][y][z].size() - 1];
				_mapa[x][y][z].pop_back();
				//std::cout << "DEBUG: TILE REMOVIDO" << std::endl;

			}
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
				Tipo
				Posicion cuadro x y capa
				Rect textura x y
				Colision
				Tipotile
	*/

	std::ofstream archivoOut;
	archivoOut.open(nombre_archivo);
	if (archivoOut.is_open())
	{
		archivoOut	<< _tamanioMaxCuadros.x << " " << _tamanioMaxCuadros.y << "\n"
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
						for (int C = 0; C < _mapa[x][y][z].size(); C++)
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
		std::string archivoTextura = "";
		sf::Vector2u tamanio;
		int tamanioCuadro = 0;
		int capas = 0;
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
		_tamanioMaxMundo.x = static_cast<float>(tamanio.x * tamanioCuadro);
		_tamanioMaxMundo.y = static_cast<float>(tamanio.y * tamanioCuadro);
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


		while (archivoIn >> x >> y >> z >> tipo)
		{
			if (tipo == tipo_tile::SPAWNERENEMIGO)
			{
				int tipoEnemigo = 0;
				int cantEnemigos = 0;
				int tiempoSpawn = 0;
				int distanciaMax = 0;

				archivoIn >> trX >> trY >> tipoEnemigo >> cantEnemigos >> tiempoSpawn >> distanciaMax;

				_mapa[x][y][z].push_back(new SpawnerEnemigos(x, y, _tamanioCuadroF, _texturaTile, sf::IntRect(trX, trY, _tamanioCuadroI, _tamanioCuadroI), tipoEnemigo, cantEnemigos, tiempoSpawn, distanciaMax));
			}
			else
			{
				archivoIn >> trX >> trY >> colision;
				_mapa[x][y][z].push_back(new TileNormal(tipo, x, y, _tamanioCuadroF, _texturaTile, sf::IntRect(trX, trY, _tamanioCuadroI, _tamanioCuadroI), colision));
			}
		}
		 //Carga todos los tiles
		/*while (archivoIn >> x >> y >> z >> trX >> trY >> colision)
		{
			_mapa[x][y][z].push_back(new Tile(tipo, x, y, _tamanioCuadroF, _texturaTile, sf::IntRect(trX, trY, _tamanioCuadroI, _tamanioCuadroI), colision));
		}*/
	}
	else
	{
		std::cout << "ERROR::TILEMAP::NO SE PUDO CARGAR DESDE ARCHIVO::" << nombre_archivo << "\n";
	}

	archivoIn.close();
}

void TileMap::actualizarLimitesMapa(Entidades* entidad, const float& DT)
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
}

void TileMap::checkColision(Entidades* entidad, const float& DT)
{
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
			for (int C = 0; C < _mapa[x][y][_capa].size(); C++)
			{
				_mapa[x][y][_capa][C]->actualizar();

				sf::FloatRect limitesJugador = entidad->getLimites();
				sf::FloatRect limitesMuros = _mapa[x][y][_capa][C]->getLimites();
				sf::FloatRect limitesPosSiguiente = entidad->getLimitesPosSiguiente(DT);

				if (this->_mapa[x][y][_capa][C]->getColision() &&
					this->_mapa[x][y][_capa][C]->interseccion(limitesPosSiguiente)
					)
				{
					//Colision Derecha
					if (limitesJugador.left < limitesMuros.left
						&& limitesJugador.left + limitesJugador.width < limitesMuros.left + limitesMuros.width
						&& limitesJugador.top < limitesMuros.top + limitesMuros.height
						&& limitesJugador.top + limitesJugador.height > limitesMuros.top
						)
					{
						entidad->detenerX();
						entidad->setPosicion(limitesMuros.left - limitesJugador.width, limitesJugador.top);
					}

					//Colision Izquierda
					else if (limitesJugador.left > limitesMuros.left
						&& limitesJugador.left + limitesJugador.width > limitesMuros.left + limitesMuros.width
						&& limitesJugador.top < limitesMuros.top + limitesMuros.height
						&& limitesJugador.top + limitesJugador.height > limitesMuros.top
						)
					{
						entidad->detenerX();
						entidad->setPosicion(limitesMuros.left + limitesMuros.width, limitesJugador.top);
					}
					//Colision Abajo
					if (limitesJugador.top < limitesMuros.top
						&& limitesJugador.top + limitesJugador.height < limitesMuros.top + limitesMuros.height
						&& limitesJugador.left < limitesMuros.left + limitesMuros.width
						&& limitesJugador.left + limitesJugador.width > limitesMuros.left
						)
					{
						entidad->detenerY();
						entidad->setPosicion(limitesJugador.left, limitesMuros.top - limitesJugador.height);
					}

					//Colision arriba
					else if (limitesJugador.top > limitesMuros.top
						&& limitesJugador.top + limitesJugador.height > limitesMuros.top + limitesMuros.height
						&& limitesJugador.left < limitesMuros.left + limitesMuros.width
						&& limitesJugador.left + limitesJugador.width > limitesMuros.left
						)
					{
						entidad->detenerY();
						entidad->setPosicion(limitesJugador.left, limitesMuros.top + limitesMuros.height);
					}

				}
			}
		}
	}
}

void TileMap::actualizarTiles(Entidades* entidad, const float& DT, std::vector<Enemigos*>& enemigos, std::map<std::string, sf::Texture>& texturas)
{
	_capa = 0;

	_desdeX = entidad->getCuadroActual(_tamanioCuadroI).x - 15;
	if (_desdeX < 0)
		_desdeX = 0;
	else if (_desdeX > _tamanioMaxCuadros.x)
		_desdeX = _tamanioMaxCuadros.x;

	_hastaX = entidad->getCuadroActual(_tamanioCuadroI).x + 15;
	if (_hastaX < 0)
		_hastaX = 0;
	else if (_hastaX > _tamanioMaxCuadros.x)
		_hastaX = _tamanioMaxCuadros.x;

	_desdeY = entidad->getCuadroActual(_tamanioCuadroI).y - 9;
	if (_desdeY < 0)
		_desdeY = 0;
	else if (_desdeY > _tamanioMaxCuadros.y)
		_desdeY = _tamanioMaxCuadros.y;

	_hastaY = entidad->getCuadroActual(_tamanioCuadroI).y + 9;
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
				if (_mapa[x][y][_capa][C]->getTipoTile() == tipo_tile::SPAWNERENEMIGO)
				{
					SpawnerEnemigos* spawner = dynamic_cast<SpawnerEnemigos*>(_mapa[x][y][_capa][C]);
					
					if(spawner)
					{
						if(!spawner->getSpawn())
						{
							enemigos.push_back(new Demon(x * _tamanioCuadroF, y * _tamanioCuadroF, texturas["ENEMIGO_1"]));
							spawner->setSpawn(true);
						}
					}
				}

			}
		}
	}
}

const bool TileMap::verificarTipoTile(const int x, const int y, const int z, const int tipo) const
{
	if(_mapa[x][y][_capa].back()->getTipoTile() == tipo) return true;
	else return false;
}


void TileMap::renderizar(sf::RenderTarget& target, const sf::Vector2i& posicionCuadro, sf::Vector2f posicionJugador, sf::Shader* sombra, const bool mostrar_hitbox) // se puede enviar cualquier posicion (player, vista, etc)
{
	// TILES
	_capa = 0;

	_desdeX = posicionCuadro.x - 30;
	if (_desdeX < 0)
		_desdeX = 0;
	else if (_desdeX > _tamanioMaxCuadros.x)
		_desdeX = _tamanioMaxCuadros.x;

	_hastaX = posicionCuadro.x + 30;
	if (_hastaX < 0)
		_hastaX = 0;
	else if (_hastaX > _tamanioMaxCuadros.x)
		_hastaX = _tamanioMaxCuadros.x;

	_desdeY = posicionCuadro.y - 15;
	if (_desdeY < 0)
		_desdeY = 0;
	else if (_desdeY > _tamanioMaxCuadros.y)
		_desdeY = _tamanioMaxCuadros.y;

	_hastaY = posicionCuadro.y + 15;
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
				_mapa[x][y][_capa][C]->actualizar();
				
				// Orden de renderizado
				if (_mapa[x][y][_capa][C]->getTipoTile() == tipo_tile::TOP)
				{
					_pilaRenderDiferida.push(_mapa[x][y][_capa][C]);
				}
				else
				{
					if(sombra)
						_mapa[x][y][_capa][C]->renderizar(target, posicionJugador, sombra);
					else
						_mapa[x][y][_capa][C]->renderizar(target);
				}

				// Colision con tiles
				if (mostrar_hitbox)
				{
					if (_mapa[x][y][_capa][C]->getColision())
					{
						_cajaColisiones.setPosition(_mapa[x][y][_capa][C]->getPosicionTile());
						target.draw(_cajaColisiones);
					}
				}

				if (_mapa[x][y][_capa][C]->getTipoTile() == tipo_tile::SPAWNERENEMIGO)
				{
					_cajaColisiones.setPosition(_mapa[x][y][_capa][C]->getPosicionTile());
					target.draw(_cajaColisiones);
				}
			}
		}
	}
}

void TileMap::renderizacionDiferida(sf::RenderTarget& target, const sf::Vector2f posicionJugador, sf::Shader* sombra)
{
	while (!_pilaRenderDiferida.empty())
	{
		if(sombra)
			_pilaRenderDiferida.top()->renderizar(target, posicionJugador, sombra); // renderiza y lo saca de la pila
		else
			_pilaRenderDiferida.top()->renderizar(target);
		_pilaRenderDiferida.pop();
	}
}
