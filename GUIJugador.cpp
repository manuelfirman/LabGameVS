#include "stdafx.h"
#include "GUIJugador.h"

void GUIJugador::iniciarFuente()
{
	_fuenteGUI.loadFromFile("recursos/fuentes/Dosis.ttf");
}

void GUIJugador::iniciarBarraNivel()
{
	float ancho = 45.f;
	float alto = 30.f;
	float x = 40.f;
	float y = 15.f;

	_textoNivel.setFont(_fuenteGUI);
	_textoNivel.setCharacterSize(18);
	_barraNivel.setSize(sf::Vector2f(ancho, alto));
	_barraNivel.setFillColor(sf::Color(50, 50, 50, 200));
	_barraNivel.setPosition(x, y);
	_textoNivel.setPosition(_barraNivel.getPosition().x + 10.f, _barraNivel.getPosition().y + 5.f);
}

void GUIJugador::iniciarBarraHP()
{
	float ancho = 300.f;
	float alto = 20.f;
	float x = 20.f;
	float y = 60.f;

	_TamMaxBarraVida = ancho;

	_textoVida.setFont(_fuenteGUI);
	_textoVida.setCharacterSize(18);
	_barraVidaOut.setSize(sf::Vector2f(ancho, alto));
	_barraVidaOut.setFillColor(sf::Color(50, 50, 50, 200));
	_barraVidaOut.setPosition(x, y);

	_barraVidaIn.setSize(sf::Vector2f(ancho, alto));
	_barraVidaIn.setFillColor(sf::Color(250, 50, 50, 200));
	_barraVidaIn.setPosition(x, y);
	
}

void GUIJugador::iniciarBarraExp()
{
	float ancho = 300.f;
	float alto = 10.f;
	float x = 20.f;
	float y = 90.f;

	_TamMaxBarraExp = ancho;

	_textoExp.setFont(_fuenteGUI);
	_textoExp.setCharacterSize(15);
	_barraExpOut.setSize(sf::Vector2f(ancho, alto));
	_barraExpOut.setFillColor(sf::Color(50, 50, 50, 200));
	_barraExpOut.setPosition(x, y);
	_barraExpIn.setSize(sf::Vector2f(ancho, alto));
	_barraExpIn.setFillColor(sf::Color(240, 240, 30, 200));
	_barraExpIn.setPosition(x, y);
	
}

GUIJugador::GUIJugador(Jugador* jugador)
{
	_jugador = jugador;
	
	this->iniciarFuente();
	this->iniciarBarraHP();
	this->iniciarBarraExp();
	this->iniciarBarraNivel();
}

GUIJugador::~GUIJugador()
{

}

void GUIJugador::actualizarBarraExp()
{
	float porcentaje = (static_cast<float>(_jugador->getAtributos()->getExp()) / static_cast<float>(_jugador->getAtributos()->getExpSiguienteNivel()));

	_barraExpIn.setSize(sf::Vector2f(static_cast<float>(std::floor(_TamMaxBarraExp * porcentaje)), _barraExpIn.getSize().y));


	_stringExp = std::to_string(_jugador->getAtributos()->getExp()) + " / " + std::to_string(_jugador->getAtributos()->getExpSiguienteNivel());
	_textoExp.setString(_stringExp);
	
	_textoExp.setPosition(_barraExpIn.getPosition().x + 5.f, _barraExpIn.getPosition().y + 0.5f);
}

void GUIJugador::actualizarBarraHP()
{
	float porcentaje = (static_cast<float>(_jugador->getAtributos()->getHP()) / static_cast<float>(_jugador->getAtributos()->getHPMax()));
	
	_barraVidaIn.setSize(sf::Vector2f(static_cast<float>(std::floor(_TamMaxBarraVida * porcentaje)), _barraVidaIn.getSize().y));


	_stringVida = std::to_string(_jugador->getAtributos()->getHP()) + " / " + std::to_string(_jugador->getAtributos()->getHPMax());
	_textoVida.setString(_stringVida);

	_textoVida.setPosition(_barraVidaIn.getPosition().x + 10.f, _barraVidaIn.getPosition().y + 2.f);
}

void GUIJugador::actualizarBarraNivel()
{
	_stringNivel = "Lv. " + std::to_string(_jugador->getAtributos()->getNivel());
	_textoNivel.setString(_stringNivel);
}

void GUIJugador::actualizar(const float& DT)
{
	actualizarBarraHP();
	actualizarBarraExp();
	actualizarBarraNivel();

}

void GUIJugador::renderizarBarraNivel(sf::RenderTarget& target)
{
	target.draw(_barraNivel);
	target.draw(_textoNivel);
}

void GUIJugador::renderizarBarraHP(sf::RenderTarget& target)
{
	target.draw(_barraVidaOut);
	target.draw(_barraVidaIn);
	target.draw(_textoVida);
}

void GUIJugador::renderizarBarraExp(sf::RenderTarget& target)
{
	target.draw(_barraExpOut);
	target.draw(_barraExpIn);
	target.draw(_textoExp);
}

void GUIJugador::renderizar(sf::RenderTarget& target)
{
	renderizarBarraHP(target);
	renderizarBarraExp(target);
	renderizarBarraNivel(target);
}
