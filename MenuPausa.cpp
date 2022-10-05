#include "stdafx.h" // precompilado
#include "MenuPausa.h"

/// --------------------------------- CONSTRUCTOR / DESTRUCTOR ----------------------------------------
MenuPausa::MenuPausa(sf::RenderWindow& ventana, sf::Font& fuente)
	: _fuentePausa(fuente)
{
	_fondo.setSize(sf::Vector2f(static_cast<float>(ventana.getSize().x), static_cast<float>(ventana.getSize().y)));
	_fondo.setFillColor(sf::Color(20,20,20,100));

	_contenedor.setSize(sf::Vector2f(static_cast<float>(ventana.getSize().x) / 4.f, static_cast<float>(ventana.getSize().y) - 100.f));
	_contenedor.setFillColor(sf::Color(20, 20, 20, 200));

	_contenedor.setPosition(static_cast<float>(ventana.getSize().x) / 2.f - _contenedor.getSize().x / 2.f, 30.f);

	_textoPausa.setFont(fuente);
	_textoPausa.setFillColor(sf::Color(255,255,255,200));
	_textoPausa.setCharacterSize(30);
	_textoPausa.setString("PAUSA");
	_textoPausa.setPosition(_contenedor.getPosition().x + _contenedor.getSize().x / 2.f - _textoPausa.getGlobalBounds().width / 2.f, _contenedor.getPosition().y);
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

void MenuPausa::agregarBoton(const std::string key, float y, const std::string texto)
{
	float ancho = 200.f;
	float alto = 50.f;
	float x = _contenedor.getPosition().x + _contenedor.getSize().x / 2.f - ancho / 2.f;
	sf::Color colorInactivo = sf::Color(48, 132, 70, 155);
	sf::Color colorActivo = sf::Color(189, 236, 182, 155);
	sf::Color colorHover = sf::Color(208, 208, 208, 155);
	sf::Color colorTextoInactivo = sf::Color(0, 0, 0, 200);
	sf::Color colorTextoHover = sf::Color(0, 0, 0, 255);
	sf::Color colorTextoActivo = sf::Color(255, 255, 255, 200);

	_botones[key] = new gui::Boton(x, y, ancho, alto, texto, 20, _fuentePausa, colorInactivo, colorHover, colorActivo, colorTextoInactivo, colorTextoHover, colorTextoActivo);
}

/// --------------------------------- ACTUALIZAR ----------------------------------------

void MenuPausa::actualizar(const sf::Vector2f& posMouse)
{
	for (auto& i : _botones)
	{
		i.second->actualizar(posMouse);
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
