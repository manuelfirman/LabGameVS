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
}

Hitbox::~Hitbox()
{
    //dtor
}

bool Hitbox::checkInterseccion(const sf::FloatRect& frect)
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