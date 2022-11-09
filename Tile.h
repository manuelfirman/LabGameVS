#ifndef TILE_H
#define TILE_H

enum tipo_tile{ SUELO = 0, PARED, TOP, SPAWNERENEMIGO };

class Tile
{
	private:

	protected:
		sf::Sprite _tile;
		bool _colision;
		int _tipoTile;

	public:
		Tile();
		Tile(int tipo, int cuadro_x, int cuadro_y, float tamanioCuadroF, sf::Texture& textura, const sf::IntRect& rect_textura, const bool colision = false);
		virtual ~Tile();

		// Getters
		virtual const int& getTipoTile() const;
		virtual const bool& getColision() const;
		virtual const sf::Vector2f& getPosicionTile() const;
		virtual const sf::FloatRect getLimites() const;
		virtual const bool interseccion(const sf::FloatRect limites) const;

		virtual const std::string getTileString() const = 0;
		virtual void actualizar() = 0;
		virtual void renderizar(sf::RenderTarget& target, const sf::Vector2f posicionJugador = sf::Vector2f(), sf::Shader* sombra = NULL) = 0;
};

#endif // TILE