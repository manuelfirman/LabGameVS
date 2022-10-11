#ifndef TILE_H
#define TILE_H

enum tipo_tile{ SUELO = 0, PARED, TOP };

class Tile
{
	private:

	protected:
		sf::Sprite _tile;
		bool _colision;
		short _tipoTile;

	public:
		Tile();
		Tile(int cuadro_x, int cuadro_y, float tamanioCuadroF, sf::Texture& textura, const sf::IntRect& rect_textura, bool colision = false, short tipo = tipo_tile::SUELO);
		~Tile();

		// Getters
		const short& getTipoTile() const;
		const bool& getColision() const;
		const sf::Vector2f& getPosicionTile() const;
		const sf::FloatRect getLimites() const;
		const bool interseccion(const sf::FloatRect limites) const;
		const std::string getTileString() const;

		void actualizar();
		void renderizar(sf::RenderTarget& target, const sf::Vector2f posicionJugador = sf::Vector2f(), sf::Shader* sombra = NULL);
		
};

#endif // TILE