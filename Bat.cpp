#include "stdafx.h"
#include "Bat.h"

void Bat::iniciarVariables()
{

}

void Bat::iniciarIA()
{
    // _inteligenciaArtificial->AgregarOpcion();
    // 
}

void Bat::iniciarAnimaciones()
{
    // key - Velocidad animacion - inicioX - inicioY - framesX - framesY
    _animacion->agregarAnimacion("QUIETO",           6.f, 0, 2, 2, 2, 32, 32);         // Quieto
    _animacion->agregarAnimacion("CAMINAR_ABAJO",    6.f, 0, 2, 2, 2, 32, 32);   // Caminar abajo
    _animacion->agregarAnimacion("CAMINAR_ARRIBA",   6.f, 0, 0, 2, 0, 32, 32);    // Caminar arriba
    _animacion->agregarAnimacion("CAMINAR_X",        6.f, 0, 3, 2, 3, 32, 32);         // Caminar derecha
}

void Bat::iniciarGUI()
{
    _barraHP.setSize(sf::Vector2f(80.f, 5.f));
    _barraHP.setFillColor(sf::Color::Red);
    _barraHP.setPosition(_sprite.getPosition().x - _barraHP.getSize().x / 1.3f, _sprite.getPosition().y);
}

Bat::Bat(float x, float y, sf::Texture& textura, std::map<std::string, sf::SoundBuffer>& sonidos, SpawnerEnemigos& tile_spawner, Entidades& jugador) : Enemigos(tile_spawner)
{
    this->iniciarVariables();

    crearHitbox(_sprite, -25.f, 0.f, 32.f, 32.f);        // Hitbox
    crearComponenteMovimiento(80.f, 1700.f, 1000.f);    // Movimiento
    crearComponenteAnimacion(textura);                  // Animacion
    crearComponenteAtributos(1);                        // Atributos
    crearComponenteSonidos(sonidos, "BAT");                   // Sonidos
    setPosicion(x, y);                                  // Posicion
    this->iniciarAnimaciones();                         // Animaciones
    this->iniciarGUI();                                 // GUI

    _inteligenciaArtificial = new IA(jugador, *this);
}

Bat::~Bat()
{
    delete _inteligenciaArtificial;
}

void Bat::actualizarIA(const float DT)
{
    _inteligenciaArtificial->seguir(DT);
    // _inteligenciaArtificial->atacar();
    // _inteligenciaArtificial->
}

void Bat::actualizarAnimacion(const float& DT)
{
    if (_movimiento->getEstadoMov(QUIETO))
    {
        _animacion->play("QUIETO", DT);
    }
    else if (_movimiento->getEstadoMov(MOV_DERECHA))
    {
        _sprite.setOrigin((_sprite.getGlobalBounds().width / 2.f) + (_hitbox->getLimites().width / 2.f), 0.f);
        _sprite.setScale(1.f, 1.f);
        _animacion->play("CAMINAR_X", DT, _movimiento->getVelocidad().x, _movimiento->getVelocidadMax());
    }
    else if (_movimiento->getEstadoMov(MOV_IZQUIERDA))
    {
        _sprite.setOrigin(0.f, 0.f);
        _sprite.setScale(-1.f, 1.f);
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


    if (_timerDmg.getElapsedTime().asMilliseconds() <= _timerDmgMax)
    {
        _sprite.setColor(sf::Color::Red);
    }
    else
    {
        _sprite.setColor(sf::Color::White);
    }
}


void Bat::actualizar(const float& DT, sf::Vector2f& posMouseVista)
{
    _movimiento->actualizar(DT);

    _barraHP.setFillColor(sf::Color::Red);
    _barraHP.setSize(sf::Vector2f(80.f * (static_cast<float>(_atributos->_hp) / _atributos->_hpMax), 5.f));
    _barraHP.setPosition(_sprite.getPosition().x - _barraHP.getSize().x / 1.3f, _sprite.getPosition().y);

    actualizarIA(DT);

    actualizarAnimacion(DT);

    _atributos->actualizar();

    _hitbox->actualizar();
}

void Bat::renderizar(sf::RenderTarget& target, sf::Shader* sombra, const sf::Vector2f posLuz, const bool mostrar_hitbox)
{
    if (sombra)
    {
        sombra->setUniform("tieneTextura", true);
        sombra->setUniform("luz", posLuz);
        target.draw(_sprite, sombra);
    }
    else // si no hay sombra
        target.draw(_sprite);

    target.draw(_barraHP);

    if (mostrar_hitbox)
        _hitbox->renderizar(target);

}