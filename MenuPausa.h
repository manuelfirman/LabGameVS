#ifndef MENUPAUSA_H
#define MENUPAUSA_H

#include "Gui.h"
#include "Audio.h"

class MenuPausa
{
	private:
		sf::RectangleShape _fondo;
		sf::RectangleShape _contenedor;
		sf::Font& _fuentePausa;
		sf::Text _textoPausa;

		std::map<std::string, gui::Boton*> _botones;
	
	public:
		MenuPausa(sf::VideoMode& modo_video, sf::Font& fuente);
		virtual ~MenuPausa();

		std::map<std::string, gui::Boton*>& getBoton();

		const bool getClick(const std::string key);
		void agregarBoton(const std::string key, const float y, const float ancho, const float alto, const unsigned tamCaracter, const std::string texto, const bool gris = false);
		void actualizar(const sf::Vector2i& posMouseVentana);
		void renderizar(sf::RenderTarget& target);
};

#endif
