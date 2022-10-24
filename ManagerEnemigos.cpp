#include "stdafx.h"
#include "ManagerEnemigos.h"

ManagerEnemigos::ManagerEnemigos(std::vector<Enemigos*>& enemigos, std::map<std::string, sf::Texture>& texturas)
	: _enemigos(enemigos), _texturas(texturas)
{

}

ManagerEnemigos::~ManagerEnemigos()
{
}

void ManagerEnemigos::crearEnemigo(const int tipo_enemigo, const int posX, const int posY)
{
	switch (tipo_enemigo)
	{
		case tipo_enemigo::DEMON:
			_enemigos.push_back(new Demon(posX, posY, _texturas["ENEMIGO_1"]));
			break;
		case tipo_enemigo::GOBLIN:
			break;
		default:
			std::cout << "ERROR::MANAGERENEMIGOS::NO EXISTE ESE TIPO DE ENEMIGO" << std::endl;
			break;
	}
}

void ManagerEnemigos::actualizar(const float& DT)
{
}

void ManagerEnemigos::renderizar(sf::RenderTarget& target)
{
}
