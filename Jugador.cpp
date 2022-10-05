#include "Jugador.h"
/// --------------------- INICIALIZACIONES --------------------------
void Jugador::iniciarVariables()
{
    _atacando = false;
}

void Jugador::iniciarComponentes()
{

}


/// --------------------- CONSTRUCTOR / DESTRUCTOR ---------------------
Jugador::Jugador(float x, float y, sf::Texture& textura)
{
    this->iniciarVariables();

    setPosicion(x, y);

    //    crearHitbox(_sprite, 0.f, 0.f, _sprite.getGlobalBounds().width, _sprite.getGlobalBounds().height);
    crearHitbox(_sprite, 18.f, 17.f, 28.f, 44.f);
    crearComponenteMovimiento(200.f, 15.f, 4.f); // Movimiento
    crearComponenteAnimacion(textura);

    // ANIMACIONES MOVIMIENTO
    _animacion->agregarAnimacion("CAMINAR_QUIETO", 10.f, 1, 10, 1, 10, 64, 64); // key - Velocidad animacion - inicioX - inicioY - framesX - framesY
    _animacion->agregarAnimacion("CAMINAR_ABAJO", 3.f, 1, 10, 8, 10, 64, 64);
    _animacion->agregarAnimacion("CAMINAR_ARRIBA", 3.f, 1, 8, 8, 8, 64, 64);
    _animacion->agregarAnimacion("CAMINAR_DERECHA", 3.f, 1, 11, 8, 11, 64, 64);
    _animacion->agregarAnimacion("CAMINAR_IZQUIERDA", 3.f, 1, 9, 8, 9, 64, 64);

    // ANIMACIONES ATAQUE
    _animacion->agregarAnimacion("ATAQUE_ARRIBA", 10.f, 1, 12, 5, 12, 64, 64);
    _animacion->agregarAnimacion("ATAQUE_IZQUIERDA", 10.f, 1, 13, 5, 13, 64, 64);
    _animacion->agregarAnimacion("ATAQUE_ABAJO", 10.f, 1, 14, 5, 14, 64, 64);
    _animacion->agregarAnimacion("ATAQUE_DERECHA", 10.f, 1, 15, 5, 15, 64, 64);


}

Jugador::~Jugador()
{
    //dtor
}

void Jugador::actualizarAtaque(const float& DT)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        _atacando = true;
    }

    if (_atacando) {
        if (_animacion->play("ATAQUE_ABAJO", DT, true)) {
            _atacando = false;

        }

    }

    //    if(_atacando){
    //        if(_movimiento->getEstadoMov(MOV_ARRIBA)){
    //            if(_animacion->play("ATAQUE_ARRIBA", DT, true)){
    //                _atacando = false;
    //            }
    //        } else if(_movimiento->getEstadoMov(MOV_ABAJO)){
    //            if(_animacion->play("ATAQUE_ABAJO", DT, true)){
    //                _atacando = false;
    //            }
    //        } else if(_movimiento->getEstadoMov(MOV_DERECHA)){
    //            if(_animacion->play("ATAQUE_DERECHA", DT, true)){
    //                _atacando = false;
    //            }
    //        }else if(_movimiento->getEstadoMov(MOV_IZQUIERDA)){
    //            if(_animacion->play("ATAQUE_IZQUIERDA", DT, true)){
    //                _atacando = false;
    //            }
    //        }
    //    }
}

void Jugador::actualizarAnimacion(const float& DT)
{
    if (_movimiento->getEstadoMov(QUIETO))
        _animacion->play("CAMINAR_QUIETO", DT);
    else if (_movimiento->getEstadoMov(MOV_DERECHA))
        _animacion->play("CAMINAR_DERECHA", DT, _movimiento->getVelocidad().x, _movimiento->getVelocidadMax());
    else if (_movimiento->getEstadoMov(MOV_IZQUIERDA))
        _animacion->play("CAMINAR_IZQUIERDA", DT, _movimiento->getVelocidad().x, _movimiento->getVelocidadMax());
    else if (_movimiento->getEstadoMov(MOV_ABAJO))
        _animacion->play("CAMINAR_ABAJO", DT, _movimiento->getVelocidad().y, _movimiento->getVelocidadMax());
    else if (_movimiento->getEstadoMov(MOV_ARRIBA))
        _animacion->play("CAMINAR_ARRIBA", DT, _movimiento->getVelocidad().y, _movimiento->getVelocidadMax());
}

void Jugador::actualizar(const float& DT)
{
    _movimiento->actualizar(DT);

    actualizarAtaque(DT);

    actualizarAnimacion(DT);

    _hitbox->actualizar();
}