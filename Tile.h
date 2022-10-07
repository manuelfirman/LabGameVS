#ifndef TILE_H
#define TILE_H

class Tile
{
	private:

	protected:
		sf::RectangleShape _tile;

	public:
		Tile();
		Tile(float x, float y, float tamanioCuadroF, sf::Texture& textura, const sf::IntRect rect_textura);
		~Tile();

		void actualizar();
		void renderizar(sf::RenderTarget& target);
		
};

#endif // TILE

