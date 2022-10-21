#include "stdafx.h"
#include "Proyectil.h"

Proyectil::Proyectil(sf::Texture& textura, float dmg, float duracion, float velocidad, sf::Vector2f direccion, sf::Vector2f inicio)
{
	_realizando = true;
	_dmg = dmg;
	_duracion = duracion;
	_velocidad = velocidad;
	_direccion = direccion;
	_inicio = inicio;

	float offsetX = 60.f;
	float offsetY = 30.f;

	_spriteSkill.setPosition(inicio.x - offsetX, inicio.y - offsetY);
	_spriteSkill.setOrigin(_spriteSkill.getGlobalBounds().width / 2.f, _spriteSkill.getGlobalBounds().height/ 2.f);
	_spriteSkill.setTexture(textura);
	_spriteSkill.setTextureRect(sf::IntRect(0, 384, 512, 384));
	_spriteSkill.setScale(0.2, 0.2);

}

Proyectil::~Proyectil()
{
}



void Proyectil::actualizar(const float& DT)
{

	if (_duracionClock.getElapsedTime().asSeconds() < _duracion)
	{
		float deltaX = _direccion.x - _inicio.x;
		float deltaY = _direccion.y - _inicio.y;
		float angulo = atan2f(deltaY, deltaX);

		sf::Vector2f velocidad;

		velocidad.x = cos(angulo) * _velocidad;
		velocidad.y = sin(angulo) * _velocidad;

		_spriteSkill.move(velocidad * DT);
	}
}

void Proyectil::renderizar(sf::RenderTarget& target)
{
	target.draw(_spriteSkill);
}

bool Proyectil::getRealizando()
{
	return _realizando;
}

bool Proyectil::eliminar()
{
	if (_duracionClock.getElapsedTime().asSeconds() < _duracion)
	{
		return false;
	}
	
	return true;
}