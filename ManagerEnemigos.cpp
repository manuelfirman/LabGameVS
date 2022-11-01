#include "stdafx.h"
#include "ManagerEnemigos.h"

ManagerEnemigos::ManagerEnemigos(std::vector<Enemigos*>& enemigos, std::map<std::string, sf::Texture>& texturas, std::map<std::string, sf::SoundBuffer>& sonidos, Entidades& jugador)
	: _enemigos(enemigos), _texturas(texturas), _sonidos(sonidos), _jugador(jugador)
{

}

ManagerEnemigos::~ManagerEnemigos()
{
}

void ManagerEnemigos::crearEnemigo(const int tipo_enemigo, const int posX, const int posY, SpawnerEnemigos& tile_spawner)
{
	switch (tipo_enemigo)
	{
		case tipo_enemigo::DEMON:
			_enemigos.push_back(new Demon(posX, posY, _texturas["DEMON"], _sonidos,  tile_spawner, _jugador));
			tile_spawner.contEnemigosMasMas(); // ++_contadorEnemigos;
			break;
		case tipo_enemigo::BAT:
			_enemigos.push_back(new Bat(posX, posY, _texturas["BAT"], _sonidos, tile_spawner, _jugador));
			tile_spawner.contEnemigosMasMas(); // ++_contadorEnemigos;
			break;
		case tipo_enemigo::SLIME:
			_enemigos.push_back(new Slime(posX, posY, _texturas["SLIME"], _sonidos, tile_spawner, _jugador));
			tile_spawner.contEnemigosMasMas(); // ++_contadorEnemigos;
			break;
		default:
			std::cout << "ERROR::MANAGERENEMIGOS::NO EXISTE ESE TIPO DE ENEMIGO" << std::endl;
			break;
	}
}

void ManagerEnemigos::eliminarEnemigo(const int indice)
{
	_enemigos[indice]->getTileSpawner().contEnemigosMenosMenos();	// --_contadorEnemigos;
	delete _enemigos[indice];										// delete enemigo
	_enemigos.erase(_enemigos.begin() + indice);					// elimino posicion
}

void ManagerEnemigos::actualizar(const float& DT)
{
}

void ManagerEnemigos::renderizar(sf::RenderTarget& target)
{
}
