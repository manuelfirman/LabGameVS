#include "stdafx.h"
#include "Espada.h"


Espada::Espada(unsigned valor, std::string ruta_textura)
	: ArmaMelee(valor, ruta_textura)
{
	//std::cout << "Test espada" << std::endl;
	// 
	// TODO: cargar la textura a traves de un puntero para no estar cargandola todo el tiempo
	if (!_texturaArma.loadFromFile("recursos/img/items/02.png"))
		std::cout << "ERROR::ARMAMELEE::NO SE PUDO CARGAR LA TEXTURA" << std::endl;


	_spriteArma.setTexture(_texturaArma);
	_spriteArma.setScale(0.5, 0.5);
	_spriteArma.setOrigin(_spriteArma.getGlobalBounds().width, _spriteArma.getGlobalBounds().height * 2.f);
	
}

Espada::~Espada()
{

}

void Espada::actualizar(const sf::Vector2f& posMouseVista, const sf::Vector2f centro)
{
	// ARMA QUE SIGUE LA POSICION DEL MOUSE
	_spriteArma.setPosition(centro);
	float dX = posMouseVista.x - _spriteArma.getPosition().x;
	float dY = posMouseVista.y - _spriteArma.getPosition().y;

	const float pi = 3.14159265f;
	float deg = atan2(dY,dX) * 180.f / pi;

	_spriteArma.setRotation(deg + 90.f);


}

void Espada::renderizar(sf::RenderTarget& target, sf::Shader* sombra)
{
	if (sombra) target.draw(_spriteArma, sombra);

	else target.draw(_spriteArma, sombra);

}

