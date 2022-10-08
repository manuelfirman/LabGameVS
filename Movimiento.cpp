#include "stdafx.h" // precompilado
#include "Movimiento.h"
/// --------------------------------- CONSTRUCTOR / DESTRUCTOR ----------------------------------------
Movimiento::Movimiento(sf::Sprite& sprite, float velocidadMaxima, float aceleracion, float desaceleracion)
    : _sprite(sprite)
{
    _velocidadMax = velocidadMaxima;
    _aceleracion = aceleracion;
    _desaceleracion = desaceleracion;
}

Movimiento::~Movimiento()
{
    //dtor
}


/// --------------------------------- METODOS ----------------------------------------
const float& Movimiento::getVelocidadMax() const
{
    return _velocidadMax;
}

const sf::Vector2f& Movimiento::getVelocidad() const
{
    return _velocidad;
}

const bool Movimiento::getEstadoMov(const int estado) const
{
    switch (estado) {
    case QUIETO:
        if (_velocidad.x == 0.f && _velocidad.y == 0.f) return true;
        return false;
        break;
    case MOVIENDO:
        if (_velocidad.x != 0.f || _velocidad.y != 0.f) return true;
        return false;
        break;
    case MOV_IZQUIERDA:
        if (_velocidad.x < 0.f) return true;
        return false;
        break;
    case MOV_DERECHA:
        if (_velocidad.x > 0.f) return true;
        return false;
        break;
    case MOV_ABAJO:
        if (_velocidad.y > 0.f) return true;
        return false;
        break;
    case MOV_ARRIBA:
        if (_velocidad.y < 0.f) return true;
        return false;
        break;
    default:
        return false;
        break;
    }
}

void Movimiento::detenerXY()
{
    // detiene en X e Y
    _velocidad.x = 0.f;
    _velocidad.y = 0.f;
}

void Movimiento::detenerX()
{
    // detiene en X
    _velocidad.x = 0.f;
}

void Movimiento::detenerY()
{
    // detiene en Y
    _velocidad.y = 0.f;
}

void Movimiento::mover(const float dir_x, const float dir_y, const float& DT)
{
    _velocidad.x += _aceleracion * dir_x * DT; /// aceleracion x
    _velocidad.y += _aceleracion * dir_y * DT; /// aceleracion y
}

/// --------------------------------- ACTUALIZAR ----------------------------------------
void Movimiento::actualizar(const float& DT)
{
    /// Limite velocidad maxima Derecha
    if (_velocidad.x > 0.f) {
        if (_velocidad.x > _velocidadMax) {
            _velocidad.x = _velocidadMax;
        }
        /// Desaceleracion Derecha
        _velocidad.x -= _desaceleracion * DT;

        if (_velocidad.x < 0.f) {
            _velocidad.x = 0.f; // Detener
        }
    }

    /// Limite velocidad maxima Izquierda
    if (_velocidad.x < 0.f) {
        if (_velocidad.x < -_velocidadMax) {
            _velocidad.x = -_velocidadMax;
        }
        /// Desaceleracion Izquierda
        _velocidad.x += _desaceleracion * DT;

        if (_velocidad.x > 0.f) {
            _velocidad.x = 0.f; // Detener
        }
    }

    /// Limite velocidad Abajo
    if (_velocidad.y > 0.f) {
        if (_velocidad.y > _velocidadMax) {
            _velocidad.y = _velocidadMax;
        }
        /// Desaceleracion hacia abajo
        _velocidad.y -= _desaceleracion * DT;

        if (_velocidad.y < 0.f) {
            _velocidad.y = 0.f; // Detener
        }
    }

    /// Limite velocidad Arriba
    if (_velocidad.y < 0.f) {
        if (_velocidad.y < -_velocidadMax) {
            _velocidad.y = -_velocidadMax;
        }
        // Desaceleracion hacia arriba
        _velocidad.y += _desaceleracion * DT;

        if (_velocidad.y > 0.f) {
            _velocidad.y = 0.f;
        }
    }


    /// Movimiento usando la velocidad
    _sprite.move(_velocidad * DT);

}