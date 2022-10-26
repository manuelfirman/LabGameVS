#ifndef TILENORMAL_H
#define TILENORMAL_H

#include "Tile.h"

class TileNormal : public Tile
{
	private:

	protected:

	public:
		TileNormal(int tipo, int cuadro_x, int cuadro_y, float tamanioCuadroF, sf::Texture& textura, const sf::IntRect& rect_textura, bool colision = false);
		~TileNormal();
				
		const std::string getTileString() const;

		void actualizar();
		void renderizar(sf::RenderTarget& target, const sf::Vector2f posicionJugador = sf::Vector2f(), sf::Shader* sombra = NULL);
};

#endif