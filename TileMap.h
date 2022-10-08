#ifndef TILEMAP_H
#define TILEMAP_H
#include "Tile.h"
#include "Entidades.h"

class Tile;
class Entidades;

class TileMap
{
	private:
		float _tamanioCuadroF;
		unsigned _tamanioCuadroU;
		unsigned _Capas;
		sf::Vector2i _tamanioMaxCuadros;
		std::vector<std::vector<std::vector<Tile*> > > _mapa;
		std::string _archivoTextura;
		sf::Texture _texturaTile;

		sf::Vector2f _tamanioMaxMundo;

		sf::RectangleShape _cajaColisiones;

		// Eliminacion de tiles
		int _desdeX;
		int _hastaX;
		int _desdeY;
		int _hastaY;
		int _capa;

	private:
		void limpiar();

	public:
		TileMap(float tamanioCuadro, int ancho, int alto, std::string archivo_textura);
		virtual ~TileMap();

		// Accesorios
		const sf::Texture* getTexturaTile() const;

		// Metodos
		void agregarTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& rect_textura, const bool& colision, const short& tipo);
		void removerTile(const unsigned x, const unsigned y, const unsigned z);

		void guardarEnArchivo(const std::string nombre_archivo);
		void cargarDesdeArchivo(const std::string nombre_archivo);

		void checkColision(Entidades* entidad, const float& DT);
		
		// Actualizar - Renderizar
		void actualizar();
		void renderizar(sf::RenderTarget& target, Entidades* entidad = NULL);

};

#endif