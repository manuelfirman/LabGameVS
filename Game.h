#ifndef GAME_H
#define GAME_H

#include "EstadoJuego.h"
#include "EstadoMenuPrincipal.h"

class Game {
private: // Atributos
	OpcionesGraficas _opcionesGraficas;
	DatosEstado _datosEstado;
	sf::RenderWindow* _ventana; // memoria dinamica
	sf::Event sfEvento;

	sf::Clock relojDt;
	float _DT;

	std::stack<EstadoBase*> _estado;
	std::map<std::string, int> _teclasSoportadas;

	float _tamanioCuadro;

private: // Metodos
	void iniciarVariables();
	void iniciarOpcionesGraficas();
	void iniciarVentana();
	void iniciarTeclas();
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
