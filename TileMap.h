#ifndef TILEMAP_H
#define TILEMAP_H
#include "Tile.h"

class Tile;

class TileMap
{
	private:
		float _tamanioCuadroF;
		unsigned _tamanioCuadroU;
		unsigned _capas;
		sf::Vector2u _tamanioMax;
		std::vector<std::vector<std::vector<Tile*> > > _mapa;
		std::string _archivoTextura;
		sf::Texture _texturaTile;

		void limpiar();

	public:
		TileMap(float tamanioCuadro, unsigned ancho, unsigned alto, std::string archivo_textura);
		virtual ~TileMap();

		// Accesorios
		const sf::Texture* getTexturaTile() const;

		// Metodos
		void agregarTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& rect_textura, const bool& colision, const short& tipo);
		void removerTile(const unsigned x, const unsigned y, const unsigned z);

		void guardarEnArchivo(const std::string nombre_archivo);
		void cargarDesdeArchivo(const std::string nombre_archivo);
		
		// Actualizar - Renderizar
		void actualizar();
		void renderizar(sf::RenderTarget& target);

};

#endif