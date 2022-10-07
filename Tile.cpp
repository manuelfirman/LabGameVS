#include "stdafx.h" // precompilado
#include "Tile.h"

Tile::Tile()
{
	_colision = false;
	_tipo = 0;
}

Tile::Tile(unsigned cuadro_x, unsigned cuadro_y, float tamanioCuadroF, sf::Texture& textura, const sf::IntRect& rect_textura, bool colision, short tipo)
{
	_tile.setSize(sf::Vector2f(tamanioCuadroF, tamanioCuadroF));
	_tile.setFillColor(sf::Color::White);
	_tile.setOutlineThickness(1.f);
	_tile.setOutlineColor(sf::Color::Black);
	_tile.setPosition(static_cast<float>(cuadro_x) * tamanioCuadroF, static_cast<float>(cuadro_y) * tamanioCuadroF);
	_tile.setTexture(&textura);
	_tile.setTextureRect(rect_textura);

	_colision = colision;
	_tipo = tipo;

}

Tile::~Tile()
{
}

const std::string Tile::getTileString() const
{
	std::stringstream ss;

	ss << _tile.getTextureRect().left << " " << _tile.getTextureRect().top << " " << _colision << " " << _tipo;

	return ss.str();
}

void Tile::actualizar()
{
}

void Tile::renderizar(sf::RenderTarget& target)
{
	target.draw(_tile);
}
