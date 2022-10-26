#include "stdafx.h"
#include "Espada.h"


Espada::Espada(int nivel, unsigned valor, std::string ruta_textura)
	: ArmaMelee(nivel, valor, ruta_textura)
{
	if (!_texturaArma.loadFromFile(ruta_textura))
		std::cout << "ERROR::ARMAMELEE::NO SE PUDO CARGAR LA TEXTURA" << std::endl;


	_spriteArma.setTexture(_texturaArma);
	_spriteArma.setScale(0.2f, 0.2f);
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

	//_spriteArma.setRotation(deg + 90.f); // 01.png
	
	//_spriteArma.setRotation(deg); // sword2.png

	//if (_timerAtaque.getElapsedTime().asMilliseconds() < _timerAtaqueMax)
	//{

	//}



	if (_timerAtaque.getElapsedTime().asMilliseconds() < _timerAtaqueMax)
	{
		_spriteArma.rotate(15.f);
	}
	else
	{
		_spriteArma.setRotation(deg);
	}
}

void Espada::renderizar(sf::RenderTarget& target, sf::Shader* sombra)
{
	if (sombra) target.draw(_spriteArma, sombra);

	else target.draw(_spriteArma, sombra);

}

