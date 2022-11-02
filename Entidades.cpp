#include "stdafx.h" // precompilado
#include "Entidades.h"
/// --------------------- INICIALIZACIONES --------------------------
void Entidades::iniciarVariables()
{
    _movimiento = NULL;
    _animacion = NULL;
    _hitbox = NULL;
    _atributos = NULL;
    _sonido = NULL;
}

/// --------------------- CONSTRUCTOR / DESTRUCTOR ---------------------
Entidades::Entidades()
{
    this->iniciarVariables();

}

Entidades::~Entidades()
{ //TODO: se podrian meter los componentes en un array
    delete _movimiento;
    delete _animacion;
    delete _hitbox;
    delete _atributos;
    delete _sonido;
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

void Entidades::crearComponenteAtributos(const int nivel)
{
    _atributos = new Atributos(nivel);
}

void Entidades::crearComponenteAtributos(int nivel, int experiencia, int hp, int vitalidad, int fuerza, int agilidad, int destreza, int inteligencia)
{
    _atributos = new Atributos(nivel, experiencia, hp, vitalidad, fuerza, agilidad, destreza, inteligencia);
}

void Entidades::crearComponenteSonidos(std::map<std::string, sf::SoundBuffer>& sonidos, std::string prefijo)
{
    _sonido = new Sonido(sonidos, prefijo);
}

// GETTERS
const sf::Vector2f& Entidades::getPosicionSprite() const
{
    if(_hitbox)
        return _hitbox->getPosicion();

    return _sprite.getPosition();
}

const sf::Vector2f Entidades::getCentro() const
{
    if(_hitbox)
        return _hitbox->getPosicion() + sf::Vector2f(_hitbox->getLimites().width / 2.f , _hitbox->getLimites().height / 2.f);

    return _sprite.getPosition() + sf::Vector2f(_sprite.getGlobalBounds().width / 2.f, _sprite.getGlobalBounds().height / 2.f);
    
}

const sf::Vector2i Entidades::getCuadroActual(const int tamanioCuadro) const
{
    if(_hitbox)
        return sf::Vector2i(static_cast<int>(_hitbox->getPosicion().x) / tamanioCuadro, static_cast<int>(_hitbox->getPosicion().y) / tamanioCuadro);
        
    return sf::Vector2i(static_cast<int>(_sprite.getPosition().x) / tamanioCuadro, static_cast<int>(_sprite.getPosition().y) / tamanioCuadro);

}

const sf::FloatRect Entidades::getLimites() const
{
    return _hitbox->getLimites();
}

const sf::FloatRect Entidades::getLimitesPosSiguiente(const float& DT) const
{
    if (_hitbox && _movimiento)
    {
        return _hitbox->getPosicionSiguiente(_movimiento->getVelocidad() * DT);
    }
    return sf::FloatRect(-1.f, -1.f, -1.f, -1.f); // para no retornar basura
}

const bool Entidades::getEnMovimiento() const
{
    return _movimiento->getEstadoMov(MOVIENDO);
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

Sonido& Entidades::getSonido()
{
    return *_sonido;
}

const float Entidades::getDistancia(const Entidades& entidad) const
{
    // (x2 - x1)^2 + (y2 - y1)^2
    //std::cout << sqrt(pow((getCentro().x - entidad.getCentro().x), 2) + pow((getCentro().y - entidad.getCentro().y), 2)) << std::endl;s
    return static_cast<float>(sqrt(pow((getCentro().x - entidad.getCentro().x), 2) + pow((getCentro().y - entidad.getCentro().y), 2)));
}
