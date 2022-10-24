#include "stdafx.h"
#include "TileNormal.h"

TileNormal::TileNormal(int tipo, int cuadro_x, int cuadro_y, float tamanioCuadroF, sf::Texture& textura, const sf::IntRect& rect_textura, bool colision)
	: Tile(tipo, cuadro_x, cuadro_y, tamanioCuadroF, textura, rect_textura, colision)
{
}

TileNormal::~TileNormal()
{
}


const std::string TileNormal::getTileString() const
{
	std::stringstream ss;

	ss << _tipoTile << " " << _tile.getTextureRect().left << " " << _tile.getTextureRect().top << " " << _colision;

	return ss.str();
}

void TileNormal::actualizar()
{
}

void TileNormal::renderizar(sf::RenderTarget& target, const sf::Vector2f posicionJugador, sf::Shader* sombra)
{
	if (sombra)
	{
		sombra->setUniform("tieneTextura", true);
		sombra->setUniform("luz", posicionJugador);

		target.draw(_tile, sombra);
	}
	else
	{
		target.draw(_tile);
	}
}
