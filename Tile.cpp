#include "stdafx.h" // precompilado
#include "Tile.h"

Tile::Tile()
{

}

Tile::Tile(float x, float y, float tamanioCuadroF)
{
	_tile.setSize(sf::Vector2f(tamanioCuadroF, tamanioCuadroF));
	_tile.setFillColor(sf::Color::White);
	_tile.setOutlineThickness(1.f);
	_tile.setOutlineColor(sf::Color::Black);
	_tile.setPosition(x, y);
}

Tile::~Tile()
{
}

void Tile::actualizar()
{
}

void Tile::renderizar(sf::RenderTarget& target)
{
	target.draw(_tile);
}
