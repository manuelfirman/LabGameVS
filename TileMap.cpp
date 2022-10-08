#include "stdafx.h" // precompilado
#include "TileMap.h"

void TileMap::limpiar()
{
	for (size_t x = 0; x < _tamanioMaxCuadros.x; x++)
	{
		for (size_t y = 0; y < _tamanioMaxCuadros.x; y++)
		{
			for (size_t z = 0; z < _Capas; z++)
			{
				delete _mapa[x][y][z]; // borra el anterior
				_mapa[x][y][z] = NULL; // habilita de nuevo
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
	_tamanioCuadroU = static_cast<unsigned>(_tamanioCuadroF);
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

	_mapa.resize(_tamanioMaxCuadros.x, std::vector<std::vector<Tile*>>());

	for (size_t x = 0; x < _tamanioMaxCuadros.x; x++) // pushea Tiles vacios
	{
		for (size_t y = 0; y < _tamanioMaxCuadros.x; y++)
		{
			_mapa[x].resize(_tamanioMaxCuadros.y, std::vector<Tile*>());
		
			for (size_t z = 0; z < _Capas; z++)
			{
				_mapa[x][y].resize(_Capas, NULL);
			}
		}
	}
	
	if (!_texturaTile.loadFromFile(archivo_textura))
		std::cout << "ERROR:TILEMAP::NO SE PUDO CARGAR PLANTILLA TEXTURA::" << archivo_textura << "\n";

	_cajaColisiones.setSize(sf::Vector2f(tamanioCuadro, tamanioCuadro));
	_cajaColisiones.setFillColor(sf::Color(255, 0, 0, 50));
	_cajaColisiones.setOutlineColor(sf::Color::Red);
	_cajaColisiones.setOutlineThickness(-1.f);
}

TileMap::~TileMap()
{
	limpiar();
}

const sf::Texture* TileMap::getTexturaTile() const
{
	return &_texturaTile;
}

void TileMap::agregarTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& rect_textura, const bool& colision, const short& tipo)
{
	// Agrega un tile en la posicion del mouse si la matriz del mapa lo permite
	if ((x < _tamanioMaxCuadros.x) && (x >= 0) && 
		(y < _tamanioMaxCuadros.y) && (x >= 0) &&
		(z <= _Capas) && (z >= 0))
	{
		if (_mapa[x][y][z] == NULL)
		{
			// se puede agregar tile
			_mapa[x][y][z] = new Tile(x, y, _tamanioCuadroF, _texturaTile, rect_textura, colision, tipo);
			std::cout << "DEBUG: TILE AGREGADO" << std::endl;
		}
	}
}

void TileMap::removerTile(const unsigned x, const unsigned y, const unsigned z)
{
	// Quita un tile en la posicion del mouse si la matriz del mapa lo permite
	if ((x < _tamanioMaxCuadros.x) && (x >= 0) &&
		(y < _tamanioMaxCuadros.y) && (x >= 0) &&
		(z <= _Capas) && (z >= 0))
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
				<< _tamanioCuadroU << "\n"
				<< _Capas << "\n"
				<< _archivoTextura << "\n";

		for (size_t x = 0; x < _tamanioMaxCuadros.x; x++)
		{
			for (size_t y = 0; y < _tamanioMaxCuadros.x; y++)
			{
				for (size_t z = 0; z < _Capas; z++)
				{
					if(_mapa[x][y][z]) // si no apunta a null
					archivoOut << x << " " << y << " " << z << " " << _mapa[x][y][z]->getTileString() << " "; // NO GUARDAR EL ULTIMO ESPACIO
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
		unsigned tamanioCuadro = 0;
		unsigned capas = 0;
		std::string archivoTextura = "";
		unsigned x = 0;
		unsigned y = 0;
		unsigned z = 0;
		unsigned trX = 0;
		unsigned trY = 0;
		bool colision = false;
		short tipo = 0;

		// Basicos
		archivoIn >> tamanio.x >> tamanio.y >> tamanioCuadro >> capas >> archivoTextura;
		
		// Tiles
		_tamanioCuadroF = static_cast<float>(tamanioCuadro);
		_tamanioCuadroU = tamanioCuadro;
		_tamanioMaxCuadros.x = tamanio.x;
		_tamanioMaxCuadros.y = tamanio.y;
		_Capas = capas;
		_archivoTextura = archivoTextura;

		limpiar();

		_mapa.resize(_tamanioMaxCuadros.x, std::vector<std::vector<Tile*> >());
		for (size_t x = 0; x < _tamanioMaxCuadros.x; x++)
		{
			for (size_t y = 0; y < _tamanioMaxCuadros.x; y++)
			{
				_mapa[x].resize(_tamanioMaxCuadros.y, std::vector<Tile*>());

				for (size_t z = 0; z < _Capas; z++)
				{
					_mapa[x][y].resize(_Capas, NULL);
				}
			}
		}

		if (!_texturaTile.loadFromFile(_archivoTextura))
			std::cout << "ERROR:TILEMAP::NO SE PUDO CARGAR PLANTILLA TEXTURA::" << _archivoTextura << "\n";

		
		// Carga todos los tiles
		while (archivoIn >> x >> y >> z >> trX >> trY >> colision >> tipo)
		{
			_mapa[x][y][z] = new Tile(
				x, y, 
				_tamanioCuadroF, 
				_texturaTile, 
				sf::IntRect(trX, trY, _tamanioCuadroU, _tamanioCuadroU), 
				colision, 
				tipo);
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
		entidad->setPosicion(0.f, entidad->getPosicionSprite().y);
		entidad->detenerX();
	}
	else if (entidad->getPosicionSprite().x + entidad->getLimites().width > _tamanioMaxMundo.x)
	{
		entidad->setPosicion(_tamanioMaxMundo.x - entidad->getLimites().width, entidad->getPosicionSprite().y);
		entidad->detenerX();
	}
		// Superior / Inferior
	if (entidad->getPosicionSprite().y < 0.f)
	{
		entidad->setPosicion(entidad->getPosicionSprite().x, 0.f);
		entidad->detenerY();
	}
	else if (entidad->getPosicionSprite().y + entidad->getLimites().height > _tamanioMaxMundo.y)
	{
		entidad->setPosicion(entidad->getPosicionSprite().x, _tamanioMaxMundo.y - entidad->getLimites().height);
		entidad->detenerY();
	}

	// TILES
	_capa = 0;

	_desdeX = entidad->getCuadroActual(_tamanioCuadroU).x - 1;
	if (_desdeX < 0)
		_desdeX = 0;
	else if (_desdeX > _tamanioMaxCuadros.x)
		_desdeX = _tamanioMaxCuadros.x;

	_hastaX = entidad->getCuadroActual(_tamanioCuadroU).x + 2;
	if (_hastaX < 0)
		_hastaX = 0;
	else if (_hastaX > _tamanioMaxCuadros.x)
		_hastaX = _tamanioMaxCuadros.x;

	_desdeY = entidad->getCuadroActual(_tamanioCuadroU).y - 1;
	if (_desdeY < 0)
		_desdeY = 0;
	else if (_desdeY > _tamanioMaxCuadros.x)
		_desdeY = _tamanioMaxCuadros.y;

	_hastaY = entidad->getCuadroActual(_tamanioCuadroU).y + 2;
	if (_hastaY < 0)
		_hastaY = 0;
	else if (_hastaY > _tamanioMaxCuadros.x)
		_hastaY = _tamanioMaxCuadros.y;


	//
	for (size_t x = _desdeX; x < _hastaX; x++)
	{
		for (size_t y = _desdeY; y < _hastaY; y++)
		{
			sf::FloatRect limitesJugador = entidad->getLimites();
			sf::FloatRect limitesPared = _mapa[x][y][_capa]->getLimites();
			sf::FloatRect limitesPosSiguiente = entidad->getLimitesPosSiguiente(DT);

			if (_mapa[x][y][_capa]->getColision() &&
				_mapa[x][y][_capa]->interseccion(limitesPosSiguiente))
			{
				// derecha
				if (limitesJugador.left < limitesPared.left
					&& limitesJugador.left + limitesJugador.width < limitesPared.left + limitesPared.width
					&& limitesJugador.top < limitesPared.top + limitesPared.height
					&& limitesJugador.top + limitesJugador.height > limitesPared.top
					)
				{
					entidad->detenerX();
					entidad->setPosicion(limitesPared.left - limitesJugador.width, limitesJugador.top);
				}
				// izquierda
				else if (limitesJugador.left > limitesPared.left
					&& limitesJugador.left + limitesJugador.width > limitesPared.left + limitesPared.width
					&& limitesJugador.top < limitesPared.top + limitesPared.height
					&& limitesJugador.top + limitesJugador.height > limitesPared.top
					)
				{
					entidad->detenerX();
					entidad->setPosicion(limitesPared.left + limitesPared.width, limitesJugador.top);
				}


				// Colision arriba
				if (limitesJugador.top > limitesPared.top &&
					limitesJugador.top + limitesJugador.height > limitesPared.top + limitesPared.height &&
					limitesJugador.left < limitesPared.left + limitesPared.width &&
					limitesJugador.left + limitesJugador.width > limitesPared.left)
				{
					entidad->detenerY();
					entidad->setPosicion(limitesJugador.left, limitesPared.top + limitesJugador.height);
				}
				// Colision abajo
				else if (limitesJugador.top < limitesPared.top &&
						limitesJugador.top + limitesJugador.height < limitesPared.top + limitesPared.height &&
						limitesJugador.left < limitesPared.left + limitesPared.width &&
						limitesJugador.left + limitesJugador.width > limitesPared.left)
				{
						entidad->detenerY();
						entidad->setPosicion(limitesJugador.left, limitesPared.top - limitesJugador.height);
				}
				
				


			}
		}
	}
	
}

void TileMap::actualizar()
{

}

void TileMap::renderizar(sf::RenderTarget& target, Entidades* entidad)
{
	// TILES
	if (entidad)
	{
		_capa = 0;

		_desdeX = entidad->getCuadroActual(_tamanioCuadroU).x - 5;
		if (_desdeX < 0)
			_desdeX = 0;
		else if (_desdeX > _tamanioMaxCuadros.x)
			_desdeX = _tamanioMaxCuadros.x;

		_hastaX = entidad->getCuadroActual(_tamanioCuadroU).x + 8;
		if (_hastaX < 0)
			_hastaX = 0;
		else if (_hastaX > _tamanioMaxCuadros.x)
			_hastaX = _tamanioMaxCuadros.x;

		_desdeY = entidad->getCuadroActual(_tamanioCuadroU).y - 5;
		if (_desdeY < 0)
			_desdeY = 0;
		else if (_desdeY > _tamanioMaxCuadros.x)
			_desdeY = _tamanioMaxCuadros.y;

		_hastaY = entidad->getCuadroActual(_tamanioCuadroU).y + 8;
		if (_hastaY < 0)
			_hastaY = 0;
		else if (_hastaY > _tamanioMaxCuadros.x)
			_hastaY = _tamanioMaxCuadros.y;

		//std::cout << _desdeX << " " << _hastaX << "\n";
		//std::cout << _desdeY << " " << _hastaY << "\n";

		for (int x = _desdeX; x < _hastaX; x++)
		{
			for (int y = _desdeY; y < _hastaY; y++)
			{
				_mapa[x][y][_capa]->renderizar(target);
				if (_mapa[x][y][_capa]->getColision())
				{
					_cajaColisiones.setPosition(_mapa[x][y][_capa]->getPosicionTile());
					target.draw(_cajaColisiones);
				}
			}
		}
	}
	else
	{
		for (auto& x : _mapa)
		{
			for(auto &y : x) // x es una matriz
			{
				for (auto* z : y) // for para las capas - pasa por Y y nos da el tile
				{
					// no renderiza vacios
					if (z != nullptr)
					{
						z->renderizar(target);
					
						if (z->getColision())
						{
							_cajaColisiones.setPosition(z->getPosicionTile());
							target.draw(_cajaColisiones);
						}
					}
				}
			}
		}
		 //No se renderiza nada que no este dentro de la ventana (cuadricula _mapa)

	}





}