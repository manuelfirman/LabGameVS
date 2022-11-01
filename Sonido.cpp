#include "stdafx.h"
#include "Sonido.h"

Sonido::Sonido()
{

}

Sonido::~Sonido()
{

}

void Sonido::agregarSonido(std::string nombre_sonido, std::string ruta_sonido)
{
	_buffer[nombre_sonido].loadFromFile(ruta_sonido);
}


void Sonido::play(std::string nombre_sonido)
{
	_sonido.resetBuffer();
	_sonido.setBuffer(_buffer[nombre_sonido]);
	_sonido.play();
}
