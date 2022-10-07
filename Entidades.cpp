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

const sf::Vector2f& Entidades::getPosicionSprite() const
{
    return _sprite.getPosition();
}


void Entidades::setPosicion(const float x, const float y)
{
    _sprite.setPosition(x, y);
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
    target.draw(_sprite);

    if (_hitbox) {
        _hitbox->renderizar(target);
    }
}