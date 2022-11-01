#include "stdafx.h"
#include "Audio.h"

Audio::Audio(const std::string ruta_musica, std::map<std::string, sf::SoundBuffer>& buffers_sonido) : _bufferSonido(buffers_sonido)
{
	if(!_musica.openFromFile(ruta_musica))
		std::cout << "ERROR::AUDIO::NOSE PUDO CARGAR MUSICA: " << ruta_musica << std::endl;
	
	_musica.setLoop(true);
	_musica.setVolume(50);

	_sonido.setVolume(50);
}

Audio::~Audio()
{

}

void Audio::playMusica()
{
	_musica.play();
}

void Audio::stopMusica()
{
	_musica.stop();
}

void Audio::playSonido(const std::string nombre_sonido)
{
	_sonido.resetBuffer();
	_sonido.setBuffer(_bufferSonido[nombre_sonido]);
	_sonido.play();
}

