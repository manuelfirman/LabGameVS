#include "stdafx.h"
#include "Animacion2.h"



// Constructor/Dtor
Animacion2::Animacion2(sf::Sprite& sprite, sf::Texture& textura, float tiempoAnimacion, int inicio_x, int inicio_y, int frames_x, int frames_y, int ancho, int alto)
    : _spriteA(sprite), _texturaA(textura), _ancho(ancho), _alto(alto), _tiempoAnimacion(tiempoAnimacion), _timer(0.f), _done(false)
{
    _cuadroInicial = sf::IntRect(inicio_x * ancho, inicio_y * alto, ancho, alto);
    _cuadroActual = _cuadroInicial;
    _cuadroFinal = sf::IntRect(frames_x * ancho, frames_y * alto, ancho, alto);

    _spriteA.setTexture(_texturaA);
    _spriteA.setTextureRect(_cuadroInicial);


}
//                ~setAnimacion();

// Metodos
const bool& Animacion2::isDone() {
    return _done;
}

const bool& Animacion2::play(const float& DT) // Normal
{
    _done = false;
    _timer += 10.f * DT;
    if (_timer >= _tiempoAnimacion) {

        _timer = 0.f; // reset timer

        if (_cuadroActual != _cuadroFinal)
        {
            _cuadroActual.left += _ancho; // Animar
            std::cout << "animando" << std::endl;
        }
        else
        {
            std::cout << "reset" << std::endl;

            _cuadroActual.left = _cuadroInicial.left; // Reset animacion
            _done = true;
        }

        _spriteA.setTextureRect(_cuadroActual);
    }
    return _done;
}


void Animacion2::reset()
{
    _timer = _tiempoAnimacion;
    _cuadroActual = _cuadroInicial;
}