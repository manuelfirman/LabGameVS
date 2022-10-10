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
		std::string _stringExp;
		sf::Text _textoExp;
		float _TamMaxBarraExp;
		sf::RectangleShape _barraExpOut;
		sf::RectangleShape _barraExpIn;


		// BARRA DE VIDA
		std::string _stringVida;
		sf::Text _textoVida;
		float _TamMaxBarraVida;
		sf::RectangleShape _barraVidaOut;
		sf::RectangleShape _barraVidaIn;

		// BARRA DE NIVEL
		std::string _stringNivel;
		sf::Text _textoNivel;
		sf::RectangleShape _barraNivel;



	private:
		void iniciarFuente();
		void iniciarBarraNivel();
		void iniciarBarraHP();
		void iniciarBarraExp();


	public:
		GUIJugador(Jugador* jugador);
		virtual ~GUIJugador();

		void actualizarBarraExp();
		void actualizarBarraHP();
		void actualizarBarraNivel();
		void actualizar(const float& DT);

		void renderizarBarraNivel(sf::RenderTarget& target);
		void renderizarBarraHP(sf::RenderTarget& target);
		void renderizarBarraExp(sf::RenderTarget& target);
		void renderizar(sf::RenderTarget& target);
	
};

#endif
