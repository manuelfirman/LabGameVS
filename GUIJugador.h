#ifndef GUIJUGADOR_H
#define GUIJUGADOR_H

#include "Jugador.h"

class Jugador;
class sf::RectangleShape;

class GUIJugador
{
	private:
		Jugador* _jugador;

		sf::Font _fuenteGUI;

		// BARRA DE EXPERIENCIA
		sf::Text _textoExp;


		// BARRA DE VIDA
		std::string _stringVida;
		sf::Text _textoVida;
		float _TamMaxBarraVida;
		sf::RectangleShape _barraVidaOut;
		sf::RectangleShape _barraVidaIn;

	private:
		void iniciarFuente();
		void iniciarBarraHP();


	public:
		GUIJugador(Jugador* jugador);
		virtual ~GUIJugador();

		void actualizarBarraHP();
		void actualizar(const float& DT);

		void renderizarBarraHP(sf::RenderTarget& target);
		void renderizar(sf::RenderTarget& target);
	
};

#endif
