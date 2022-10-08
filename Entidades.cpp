#include "stdafx.h" // precompilado
#include "Entidades.h"
/// --------------------- INICIALIZACIONES --------------------------
void Entidades::iniciarVariables()
{
    _movimiento = NULL;
    _animacion = NULL;
    _hitbox = NULL;
}

/// --------------------- CONSTRUCTOR / DESTRUCTOR ---------------------
Entidades::Entidades()
{
    this->iniciarVariables();

}

Entidades::~Entidades()
{
    delete _movimiento;
    delete _animacion;
    delete _hitbox;
}


/// --------------------- FUNCIONES ---------------------

void Entidades::setTextura(sf::Texture& textura)
{
    _sprite.setTexture(textura);
}

void Entidades::crearHitbox(sf::Sprite& sprite, float x, float y, float ancho, float alto)
{
    _hitbox = new Hitbox(sprite, x, y, ancho, alto);
}

void Entidades::crearComponenteMovimiento(float velocidadMaxima, float aceleracion, float desaceleracion)
{
    _movimiento = new Movimiento(_sprite, velocidadMaxima, aceleracion, desaceleracion);
}

void Entidades::crearComponenteAnimacion(sf::Texture& textura)
{
    _animacion = new Animacion(_sprite, textura);
}

// GETTERS
const sf::Vector2f& Entidades::getPosicionSprite() const
{
    if(_hitbox)
        return _hitbox->getPosicion();

    return _sprite.getPosition();
}

const sf::Vector2u Entidades::getCuadroActual(const unsigned tamanioCuadroU) const
{
    if(_hitbox)
        return sf::Vector2u(static_cast<unsigned>(_hitbox->getPosicion().x) / tamanioCuadroU, static_cast<unsigned>(_hitbox->getPosicion().y) / tamanioCuadroU);
        
    return sf::Vector2u(static_cast<unsigned>(_sprite.getPosition().x) / tamanioCuadroU, static_cast<unsigned>(_sprite.getPosition().y) / tamanioCuadroU);

}

const sf::FloatRect& Entidades::getLimites() const
{
    return _hitbox->getLimites();
}

const sf::FloatRect& Entidades::getLimitesPosSiguiente(const float& DT) const
{
    if (_hitbox && _movimiento)
    {
        return _hitbox->getPosicionSiguiente(_movimiento->getVelocidad() * DT);
    }
    return sf::FloatRect();
}

// 
void Entidades::setPosicion(const float x, const float y)
{
    if (_hitbox)
        _hitbox->setPosicion(x, y);
    else
        _sprite.setPosition(x, y);
}

void Entidades::detenerXY()
{
    if(_movimiento)
        _movimiento->detenerXY();
}

void Entidades::detenerX()
{
    if (_movimiento)
        _movimiento->detenerX();
}

void Entidades::detenerY()
{
    if (_movimiento)
        _movimiento->detenerY();
}

void Entidades::mover(const float dir_x, const float dir_y, const float& DT)
{
    if (this->_movimiento) {
        // Recibe direcciones (x y)
        _movimiento->mover(dir_x, dir_y, DT); // setea velocidad
    }
}


/// --------------------- ACTUALIZACIONES --------------------------
void Entidades::actualizar(const float& DT)
{


}

/// --------------------- RENDERIZAR --------------------------
void Entidades::renderizar(sf::RenderTarget& target)
{


}