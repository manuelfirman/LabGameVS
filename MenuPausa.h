#ifndef MENUPAUSA_H
#define MENUPAUSA_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <stack>
#include <map>
#include <vector>

#include "Gui.h"


class MenuPausa
{
	private:
		sf::RectangleShape _fondo;
		sf::RectangleShape _contenedor;
		sf::Font& _fuentePausa;
		sf::Text _textoPausa;

		std::map<std::string, gui::Boton*> _botones;

	
	
	public:
		MenuPausa(sf::RenderWindow& ventana, sf::Font& fuente);
		virtual ~MenuPausa();

		std::map<std::string, gui::Boton*>& getBoton();

		const bool getClick(const std::string key);
		void agregarBoton(const std::string clave, float y, const std::string texto);
		void actualizar(const sf::Vector2f& posMouse);
		void renderizar(sf::RenderTarget& target);
};

#endif
