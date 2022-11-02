#ifndef GAME_H
#define GAME_H

#include "EstadoJuego.h"
#include "EstadoMenuPrincipal.h"

class Game {
private: // Atributos
	std::stack<EstadoBase*> _estado;
	OpcionesGraficas _opcionesGraficas;
	std::map<std::string, int> _teclasSoportadas;
	sf::RenderWindow* _ventana; // memoria dinamica
	Audio* _audio;
	std::map<std::string, sf::SoundBuffer> _bufferSonidos;
	DatosEstado _datosEstado;

	sf::Event sfEvento;

	sf::Clock relojDt;
	float _DT;


	float _tamanioCuadro;

private: // Metodos
	void iniciarVariables();
	void iniciarOpcionesGraficas();
	void iniciarVentana();
	void iniciarTeclas();
	void iniciarAudio();
	void iniciarDatosEstado();
	void iniciarEstados();

public:
	Game();
	~Game();


	/// Actualizar
	void actualizarDT();
	void actualizarEventosSFML();
	void actualizar();

	/// Renderizar
	void renderizar();

	/// Core
	void gameloop();

	void finAplicacion();
};

#endif // GAME_H
