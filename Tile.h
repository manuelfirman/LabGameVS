#ifndef TILE_H
#define TILE_H

enum TipoTile{DEFAULT = 0, DAMAGING};

class Tile
{
	private:

	protected:
		sf::RectangleShape _tile;
		bool _colision;
		short _tipo;

	public:
		Tile();
		Tile(int cuadro_x, int cuadro_y, float tamanioCuadroF, sf::Texture& textura, const sf::IntRect& rect_textura, bool colision = false, short tipo = TipoTile::DEFAULT);
		~Tile();

		const bool& getColision() const;
		const sf::Vector2f& getPosicionTile() const;
		const sf::FloatRect getLimites() const;
		const bool interseccion(const sf::FloatRect limites) const;
		const std::string getTileString() const;

		void actualizar();
		void renderizar(sf::RenderTarget& target);
		
};

#endif // TILE

