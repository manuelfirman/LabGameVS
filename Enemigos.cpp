#include "stdafx.h"
#include "Enemigos.h"

void Enemigos::iniciarVariables()
{
  
}


void Enemigos::iniciarAnimaciones()
{
    // key - Velocidad animacion - inicioX - inicioY - framesX - framesY
    _animacion->agregarAnimacion("QUIETO", 6.f, 0, 0, 2, 0, 64, 64);         // Quieto
    _animacion->agregarAnimacion("CAMINAR_ABAJO", 6.f, 0, 0, 3, 0, 64, 64);   // Caminar abajo
    _animacion->agregarAnimacion("CAMINAR_ARRIBA", 6.f, 0, 1, 3, 1, 64, 64);    // Caminar arriba
    _animacion->agregarAnimacion("CAMINAR_X", 6.f, 0, 2, 3, 2, 64, 64);         // Caminar derecha
    //_animacion->agregarAnimacion("CAMINAR_X", 3.f, 1, 11, 8, 11, 64, 64);       // Caminar izquierda

     // ANIMACIONES ATAQUE
    
    _animacion->agregarAnimacion("ATAQUE_ABAJO", 10.f, 1, 14, 5, 14, 64, 64);
    _animacion->agregarAnimacion("ATAQUE_X", 10.f, 1, 13, 5, 13, 64, 64);
}

Enemigos::Enemigos(float x, float y, sf::Texture& textura)
   /* : _spawner(spawner)*/
{
    this->iniciarVariables();

    crearHitbox(_sprite, 18.f, 7.f, 28.f, 40.f);       // Hitbox
    crearComponenteMovimiento(150.f, 1700.f, 1000.f);   // Movimiento
    crearComponenteAnimacion(textura);                  // Animacion
    setPosicion(x, y);                                  // Posicion
    this->iniciarAnimaciones();                         // Animaciones
}

Enemigos::~Enemigos()
{
}

void Enemigos::actualizarAnimacion(const float& DT)
{
    if (_movimiento->getEstadoMov(QUIETO))
    {
        _animacion->play("QUIETO", DT);
    }
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
    {
        _animacion->play("CAMINAR_ABAJO", DT, _movimiento->getVelocidad().y, _movimiento->getVelocidadMax());
    }
    else if (_movimiento->getEstadoMov(MOV_ARRIBA))
    {
        _animacion->play("CAMINAR_ARRIBA", DT, _movimiento->getVelocidad().y, _movimiento->getVelocidadMax());
    }

}


void Enemigos::actualizar(const float& DT, sf::Vector2f& posMouseVista)
{
    _movimiento->actualizar(DT);

    //actualizarAtaque(DT, posMouseVista);

    actualizarAnimacion(DT);

    _hitbox->actualizar();
}

void Enemigos::renderizar(sf::RenderTarget& target, sf::Shader* sombra, const sf::Vector2f posLuz, const bool mostrar_hitbox)
{
    if (sombra)
    {
        sombra->setUniform("tieneTextura", true);
        sombra->setUniform("luz", posLuz);
        target.draw(_sprite, sombra);
    }
    else // si no hay sombra
        target.draw(_sprite);


    if (mostrar_hitbox)
        _hitbox->renderizar(target);
}