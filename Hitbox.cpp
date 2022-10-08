#include "stdafx.h" // precompilado
#include "Hitbox.h"

Hitbox::Hitbox(sf::Sprite& sprite, float x, float y, float ancho, float alto)
    : _sprite(sprite), _offsetX(x), _offsetY(y)
{
    _hitbox.setPosition(_sprite.getPosition().x + x, _sprite.getPosition().y + y);
    _hitbox.setSize(sf::Vector2f(ancho, alto));
    _hitbox.setFillColor(sf::Color::Transparent);
    _hitbox.setOutlineThickness(1.f);
    _hitbox.setOutlineColor(sf::Color::Green);

    _posicionSiguiente.left = 0.f;
    _posicionSiguiente.top = 0.f;
    _posicionSiguiente.width = ancho;
    _posicionSiguiente.height = alto;
}

Hitbox::~Hitbox()
{
    //dtor
}

void Hitbox::setPosicion(const sf::Vector2f& posicion)
{
    _hitbox.setPosition(posicion);
    _sprite.setPosition(posicion.x - _offsetX, posicion.y - _offsetY);
}

void Hitbox::setPosicion(const float x, const float y)
{
    _hitbox.setPosition(x, y);
    _sprite.setPosition(x - _offsetX, y - _offsetY);
}

const sf::Vector2f& Hitbox::getPosicion() const
{
    return _hitbox.getPosition();
}

const sf::FloatRect& Hitbox::getLimites() const
{
    return _sprite.getGlobalBounds();
}

const sf::FloatRect& Hitbox::getPosicionSiguiente(const sf::Vector2f& velocidad)
{
    _posicionSiguiente.left = _hitbox.getPosition().x + velocidad.x; // posicion actual + donde queda luego de mover el siguiente frame
    _posicionSiguiente.top = _hitbox.getPosition().y + velocidad.y;
    return _posicionSiguiente;
}


bool Hitbox::interseccion(const sf::FloatRect& frect)
{
    return _hitbox.getGlobalBounds().intersects(frect);
}

void Hitbox::actualizar()
{
    _hitbox.setPosition(_sprite.getPosition().x + _offsetX, _sprite.getPosition().y + _offsetY);
}

void Hitbox::renderizar(sf::RenderTarget& target)
{
    target.draw(_hitbox);
}