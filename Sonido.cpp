#include "stdafx.h"
#include "Sonido.h"

Sonido::Sonido(std::map<std::string, sf::SoundBuffer>& sonidos, std::string prefijo) : _buffer(sonidos)
{
	_prefijo = prefijo;
}

Sonido::~Sonido()
{

}

void Sonido::play(std::string tipo_sonido)
{
	std::string NombreSonido = _prefijo + "_" + tipo_sonido;

	//std::cout<<"debug sonido: " << NombreSonido << std::endl;

	_sonido.resetBuffer();
	_sonido.setBuffer(_buffer[NombreSonido]);
	_sonido.play();
}
