#ifndef TILE_H
#define TILE_H

class Tile
{
	private:

	protected:
		sf::RectangleShape _tile;

	public:
		Tile();
		Tile(float x, float y, float tamanioCuadroF);
		~Tile();

		void actualizar();
		void renderizar(sf::RenderTarget& target);
		
};

#endif // TILE

