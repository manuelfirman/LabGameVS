#include "stdafx.h"
#include "Audio.h"

Audio::Audio()
{
	if(!_bufferSonido["HIT_ESPADA"].loadFromFile("recursos/sonido/hit_espada.wav"))
		std::cout << "ERROR::AUDIO::NOSE PUDO CARGAR AUDIO: 'recursos/sonido/hit_espada.wav'." << std::endl;
	if(!_bufferSonido["DMG_ENEMIGO"].loadFromFile("recursos/sonido/hurt_enemigo.wav"))
		std::cout << "ERROR::AUDIO::NOSE PUDO CARGAR AUDIO: 'recursos/sonido/hit_espada.wav'." << std::endl;
	if(!_bufferSonido["DMG_JUGADOR"].loadFromFile("recursos/sonido/hit2.ogg"))
		std::cout << "ERROR::AUDIO::NOSE PUDO CARGAR AUDIO: 'recursos/sonido/hit_espada.wav'." << std::endl;



	

	//if(!_bufferSonido.loadFromFile("recursos/sonido/hurt_enemigo.wav"))
	//	std::cout << "ERROR::AUDIO::NOSE PUDO CARGAR AUDIO: 'recursos/sonido/hurt_enemigo.wav'." << std::endl;

	//_sonido["DMG_ENEMIGO"].setBuffer(_bufferSonido);


}

Audio::~Audio()
{
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

