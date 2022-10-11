#include "stdafx.h" // precompilado
#include "MenuPausa.h"

/// --------------------------------- CONSTRUCTOR / DESTRUCTOR ----------------------------------------
MenuPausa::MenuPausa(sf::VideoMode& modo_video, sf::Font& fuente)
	: _fuentePausa(fuente)
{
	_fondo.setSize(sf::Vector2f(static_cast<float>(modo_video.width), static_cast<float>(modo_video.height)));
	_fondo.setFillColor(sf::Color(20,20,20,100));

	_contenedor.setSize(sf::Vector2f(static_cast<float>(modo_video.width) / 4.f, static_cast<float>(modo_video.height) - gui::p2pY(9.2f, modo_video)));
	_contenedor.setFillColor(sf::Color(20, 20, 20, 200));

	_contenedor.setPosition(static_cast<float>(modo_video.width) / 2.f - _contenedor.getSize().x / 2.f, gui::p2pY(2.8f, modo_video));

	_textoPausa.setFont(fuente);
	_textoPausa.setFillColor(sf::Color(255,255,255,200));
	_textoPausa.setCharacterSize(gui::calcTamCaracter(modo_video));
	_textoPausa.setString("PAUSA");
	_textoPausa.setPosition(_contenedor.getPosition().x + _contenedor.getSize().x / 2.f - _textoPausa.getGlobalBounds().width / 2.f,
							_contenedor.getPosition().y + gui::p2pY(4.f, modo_video));
}

MenuPausa::~MenuPausa()
{
	auto it = _botones.begin();
	for (it = _botones.begin(); it != _botones.end(); ++it) {
		delete it->second;
	}
}

/// --------------------------------- METODOS ----------------------------------------
std::map<std::string, gui::Boton*>& MenuPausa::getBoton()
{
	return _botones;
}

const bool MenuPausa::getClick(const std::string key)
{
	return _botones[key]->getClick();
}

void MenuPausa::agregarBoton(const std::string key, const float y, const float ancho, const float alto, const unsigned tamCaracter, const std::string texto)
{
	float x = _contenedor.getPosition().x + _contenedor.getSize().x / 2.f - ancho / 2.f;
	sf::Color colorInactivo = sf::Color(48, 132, 70, 155);
	sf::Color colorActivo = sf::Color(189, 236, 182, 155);
	sf::Color colorHover = sf::Color(208, 208, 208, 155);
	sf::Color colorTextoInactivo = sf::Color(0, 0, 0, 200);
	sf::Color colorTextoHover = sf::Color(0, 0, 0, 255);
	sf::Color colorTextoActivo = sf::Color(255, 255, 255, 200);

	_botones[key] = new gui::Boton(x, y, ancho, alto, texto, tamCaracter, _fuentePausa, colorInactivo, colorHover, colorActivo, colorTextoInactivo, colorTextoHover, colorTextoActivo);
}

/// --------------------------------- ACTUALIZAR ----------------------------------------

void MenuPausa::actualizar(const sf::Vector2i& posMouseVentana)
{
	for (auto& i : _botones)
	{
		i.second->actualizar(posMouseVentana);
	}
}

/// --------------------------------- RENDERIZAR ----------------------------------------
void MenuPausa::renderizar(sf::RenderTarget& target)
{
	target.draw(_fondo);
	target.draw(_contenedor);

	for (auto& i : _botones) {
		i.second->renderizar(target);
	}

	target.draw(_textoPausa);
}
