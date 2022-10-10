#include "stdafx.h" // precompilado
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
    crearComponenteMovimiento(300.f, 1400.f, 1000.f); // Movimiento
    crearComponenteAnimacion(textura);
    crearComponenteAtributos(1);

    _animacion->agregarAnimacion("QUIETO", 10.f, 1, 10, 1, 10, 64, 64); // key - Velocidad animacion - inicioX - inicioY - framesX - framesY
    _animacion->agregarAnimacion("CAMINAR_ABAJO", 3.f, 1, 10, 8, 10, 64, 64);
    _animacion->agregarAnimacion("CAMINAR_ARRIBA", 3.f, 1, 8, 8, 8, 64, 64);
    _animacion->agregarAnimacion("CAMINAR_X", 3.f, 1, 11, 8, 11, 64, 64);
    _animacion->agregarAnimacion("CAMINAR_X", 3.f, 1, 9, 8, 9, 64, 64);

     // ANIMACIONES ATAQUE
    _animacion->agregarAnimacion("ATAQUE_ARRIBA", 10.f, 1, 12, 5, 12, 64, 64);
    _animacion->agregarAnimacion("ATAQUE_ABAJO", 10.f, 1, 14, 5, 14, 64, 64);
    _animacion->agregarAnimacion("ATAQUE_X", 10.f, 1, 13, 5, 13, 64, 64);


    //// ANIMACIONES MOVIMIENTO ((((PELADO)))
    //crearHitbox(_sprite, 86.f, 60.f, 86.f, 118.f);
    //_animacion->agregarAnimacion("QUIETO", 10.f, 0, 0, 13, 0, 192, 192);
    //_animacion->agregarAnimacion("CAMINAR", 6.f, 0, 1, 11, 1, 192, 192);
    //_animacion->agregarAnimacion("ATACAR", 5.f, 0, 2, 13, 2, 192 * 2, 192);


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

       


    //if (_atacando) {
    //    if (_movimiento->getEstadoMov(QUIETO))
    //    {
    //        if (_animacion->play("ATAQUE_X", DT, true)) 
    //            _atacando = false;
    //    }
    //    else if (_movimiento->getEstadoMov(MOV_DERECHA) || _movimiento->getEstadoMov(MOV_ARRIBA))
    //    {
    //        _sprite.setOrigin(_sprite.getGlobalBounds().width, 0.f);
    //        _sprite.setScale(-1.f, 1.f);
    //        if(_animacion->play("ATAQUE_X", DT, true))
    //            _atacando = false;
    //    }
    //    else if (_movimiento->getEstadoMov(MOV_IZQUIERDA) || _movimiento->getEstadoMov(MOV_ARRIBA))
    //    {
    //        _sprite.setOrigin(0.f, 0.f);
    //        _sprite.setScale(1.f, 1.f);
    //        if(_animacion->play("ATAQUE_X", DT, true))
    //            _atacando = false;
    //    }
    //    else if (_movimiento->getEstadoMov(MOV_ABAJO))
    //    {
    //        if(_animacion->play("ATAQUE_ABAJO", DT, true))
    //            _atacando = false;
    //    }
    //    else if (_movimiento->getEstadoMov(MOV_ARRIBA))
    //    {
    //        if(_animacion->play("ATAQUE_ARRIBA", DT, true))
    //            _atacando = false;
    //    }

    //}

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
   // PELADO
    if (_atacando)
    {
        if (_sprite.getScale().x > 0.f)
        {
            _sprite.setOrigin(0.f, 0.f);
        }
        else
        {
            _sprite.setOrigin(_sprite.getGlobalBounds().width, 0.f);
        }
        
        
        if (_animacion->play("ATAQUE_X", DT, true))
            _atacando = false;
    }


   if (_movimiento->getEstadoMov(QUIETO))
        _animacion->play("QUIETO", DT);
   else if (_movimiento->getEstadoMov(MOV_DERECHA))
   {

        _sprite.setOrigin(_sprite.getGlobalBounds().width, 0.f);
        _sprite.setScale(-1.f, 1.f);
        _animacion->play("CAMINAR_X", DT, _movimiento->getVelocidad().x, _movimiento->getVelocidadMax());
   }
   else if (_movimiento->getEstadoMov(MOV_IZQUIERDA))
   {
        _sprite.setOrigin(0.f, 0.f);
        _sprite.setScale(1.f, 1.f);
        _animacion->play("CAMINAR_X", DT, _movimiento->getVelocidad().x, _movimiento->getVelocidadMax());
   }
   else if (_movimiento->getEstadoMov(MOV_ABAJO))
        _animacion->play("CAMINAR_ABAJO", DT, _movimiento->getVelocidad().y, _movimiento->getVelocidadMax());
   else if (_movimiento->getEstadoMov(MOV_ARRIBA))
        _animacion->play("CAMINAR_ARRIBA", DT, _movimiento->getVelocidad().y, _movimiento->getVelocidadMax());
    
    /// ESPADACHIN
    //if (_movimiento->getEstadoMov(QUIETO))
    //{
    //    _animacion->play("QUIETO", DT);
    //}
    //else if (_movimiento->getEstadoMov(MOV_IZQUIERDA))
    //{
    //    if (_sprite.getScale().x < 0.f)
    //    {
    //        _sprite.setOrigin(0.f, 0.f);
    //        _sprite.setScale(1.f, 1.f);
    //    }
    //    _animacion->play("CAMINAR", DT);
    //}
    //else if (_movimiento->getEstadoMov(MOV_DERECHA))
    //{
    //    if (_sprite.getScale().x > 0.f)
    //    {
    //        _sprite.setOrigin(258.f, 0.f);
    //        _sprite.setScale(-1.f, 1.f);

    //    }
    //    _animacion->play("CAMINAR", DT);
    //}
    //else if (_movimiento->getEstadoMov(MOV_ARRIBA))
    //{
    //    _animacion->play("CAMINAR", DT);
    //}
    //else if (_movimiento->getEstadoMov(MOV_ABAJO))
    //{
    //    _animacion->play("CAMINAR", DT);
    //}
}

void Jugador::actualizar(const float& DT)
{
    //_atributos->actualizar();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        _atributos->subirExp(20);

    std::cout << _atributos->debug() << "\n";

    _movimiento->actualizar(DT);

    actualizarAtaque(DT);

    actualizarAnimacion(DT);

    _hitbox->actualizar();
}

void Jugador::renderizar(sf::RenderTarget& target)
{
    target.draw(_sprite);

    _hitbox->renderizar(target);
}
