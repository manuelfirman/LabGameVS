#include "stdafx.h" // precompilado
#include "Animacion.h"

/// --------------------------------- CONSTRUCTOR / DESTRUCTOR ----------------------------------------
Animacion::Animacion(sf::Sprite& sprite, sf::Texture& textura)
    : _spriteCA(sprite), _texturaCA(textura), _ultimaAnimacion(NULL), _animacionPrioritaria(NULL)
{
    //ctor
}

Animacion::~Animacion()
{
    for (auto& animaciones : _animaciones) {
        delete animaciones.second;
    }
}

/// --------------------------------- METODOS ----------------------------------------

const bool& Animacion::isDone(const std::string key)
{
    return _animaciones[key]->isDone();
}

void Animacion::agregarAnimacion(const std::string key, float tiempoAnimacion, int inicio_x, int inicio_y, int frames_x, int frames_y, int ancho, int alto)
{
    _animaciones[key] = new setAnimacion(_spriteCA, _texturaCA, tiempoAnimacion, inicio_x, inicio_y, frames_x, frames_y, ancho, alto);
}


/// --------------------------------- PLAY SOBRECARGADO (con y sin modificadores de velocidad)----------------------------------------
const bool& Animacion::play(const std::string key, const float& DT, const bool prioridad)
{
    if (_animacionPrioritaria)
    { // Animaciones con prioridad
        if (_animacionPrioritaria == _animaciones[key])
        {
            if (_ultimaAnimacion != _animaciones[key])
            {
                if (_ultimaAnimacion == NULL)
                {
                    _ultimaAnimacion = _animaciones[key];
                }
                else
                {
                    _ultimaAnimacion->reset();
                    _ultimaAnimacion = _animaciones[key];
                }
            }

            if (_animaciones[key]->play(DT)) // si termina la animacion prioritaria, la borra
            {
                _animacionPrioritaria = NULL;
            }
        }
    }
    else
    {
        // Si no hay animaciones con prioridad
        if (prioridad) {
            _animacionPrioritaria = _animaciones[key];
        }

        if (_ultimaAnimacion != _animaciones[key])
        {
            if (_ultimaAnimacion == NULL) {
                _ultimaAnimacion = _animaciones[key];
            }
            else {
                _ultimaAnimacion->reset();
                _ultimaAnimacion = _animaciones[key];
            }
        }
        _animaciones[key]->play(DT);
    }

    return _animaciones[key]->isDone();
}


const bool& Animacion::play(const std::string key, const float& DT, const float& modificador, const float& modificador_max, const bool prioridad)
{
    if (_animacionPrioritaria)
    { // Animaciones con prioridad
        if (_animacionPrioritaria == _animaciones[key])
        {
            if (_ultimaAnimacion != _animaciones[key])
            {
                if (_ultimaAnimacion == NULL) {
                    _ultimaAnimacion = _animaciones[key];
                }
                else {
                    _ultimaAnimacion->reset();
                    _ultimaAnimacion = _animaciones[key];
                }
            }
            if (_animaciones[key]->play(DT, abs(modificador / modificador_max))) // si termina la animacion prioritaria, la borra
            {
                _animacionPrioritaria = NULL;
            }
        }
    }
    else
    {
        if (prioridad) {
            _animacionPrioritaria = _animaciones[key];
        }

        if (_ultimaAnimacion != _animaciones[key])
        {
            if (_ultimaAnimacion == NULL) {
                _ultimaAnimacion = _animaciones[key];
            }
            else {
                _ultimaAnimacion->reset();
                _ultimaAnimacion = _animaciones[key];
            }
        }
        _animaciones[key]->play(DT, abs(modificador / modificador_max));
    }

    return _animaciones[key]->isDone();
}

void Animacion::test(const std::string key, const float& DT)
{
    _animaciones[key]->play(DT);
}

