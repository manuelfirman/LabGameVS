#include "stdafx.h"
#include "GUIJugador.h"

void GUIJugador::iniciarFuente()
{
	_fuenteGUI.loadFromFile("recursos/fuentes/Dosis.ttf");
}

void GUIJugador::iniciarBarraHP()
{
	float ancho = 300.f;
	float alto = 50.f;
	float x = 20.f;
	float y = 20.f;

	_TamMaxBarraVida = ancho;

	_textoVida.setFont(_fuenteGUI);

	_barraVidaOut.setSize(sf::Vector2f(ancho, alto));
	_barraVidaOut.setFillColor(sf::Color(50, 50, 50, 200));
	_barraVidaOut.setPosition(x, y);

	_barraVidaIn.setSize(sf::Vector2f(ancho, alto));
	_barraVidaIn.setFillColor(sf::Color(250, 50, 50, 200));
	_barraVidaIn.setPosition(x, y);
}

GUIJugador::GUIJugador(Jugador* jugador)
{
	_jugador = jugador;
	
	this->iniciarFuente();
	this->iniciarBarraHP();
}

GUIJugador::~GUIJugador()
{

}

void GUIJugador::actualizarBarraHP()
{
	float porcentaje = (static_cast<float>(_jugador->getAtributos()->getHP()) / static_cast<float>(_jugador->getAtributos()->getHPMax()));
	
	_barraVidaIn.setSize(sf::Vector2f(static_cast<float>(std::floor(_TamMaxBarraVida * porcentaje)), _barraVidaIn.getSize().y));


	_stringVida = std::to_string(_jugador->getAtributos()->getHP()) + " / " + std::to_string(_jugador->getAtributos()->getHPMax());
	_textoVida.setString(_stringVida);

	_textoVida.setPosition(_barraVidaIn.getPosition().x + 10.f, _barraVidaIn.getPosition().y + 5.f );
}

void GUIJugador::actualizar(const float& DT)
{
	actualizarBarraHP();

}

void GUIJugador::renderizarBarraHP(sf::RenderTarget& target)
{
	target.draw(_barraVidaOut);
	target.draw(_barraVidaIn);
	target.draw(_textoVida);
}

void GUIJugador::renderizar(sf::RenderTarget& target)
{
	renderizarBarraHP(target);
}
