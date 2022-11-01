#include "stdafx.h"
#include "Audio.h"

Audio::Audio()
{
	if(!_musicaJuego.openFromFile("recursos/sonido/bloody_sword.ogg"))
		std::cout << "ERROR::AUDIO::NOSE PUDO CARGAR MUSICA: 'recursos/sonido/bloody_sword.ogg'." << std::endl;
	
	

	//if(!_bufferSonido.loadFromFile("recursos/sonido/hurt_enemigo.wav"))
	//	std::cout << "ERROR::AUDIO::NOSE PUDO CARGAR AUDIO: 'recursos/sonido/hurt_enemigo.wav'." << std::endl;

	//_sonido["DMG_ENEMIGO"].setBuffer(_bufferSonido);


}

Audio::~Audio()
{
}



void Audio::playMusica()
{
	_musicaJuego.play();
}

void Audio::playE(const std::string nombre_sonido)
{
	_sonidoEnemigo.resetBuffer();
	_sonidoEnemigo.setBuffer(_bufferSonido[nombre_sonido]);
	_sonidoEnemigo.play();
}

void Audio::playJ(const std::string nombre_sonido)
{
	_sonidoJugador.resetBuffer();
	_sonidoJugador.setBuffer(_bufferSonido[nombre_sonido]);
	_sonidoJugador.play();
}

