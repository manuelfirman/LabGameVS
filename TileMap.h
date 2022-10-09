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
		int _tamanioCuadroI;
		int _Capas;
		sf::Vector2i _tamanioMaxCuadros;
		std::vector <std::vector < std::vector < std::vector <Tile*> > > > _mapa; // si, son 4 xD
		std::stack<Tile*> _pilaRenderDiferida;
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

		// Getters
		const sf::Texture* getTexturaTile() const;
		const int getTilesPorCuadro(const int x,const int y,const int capa) const;

		// Metodos
		void agregarTile(const int x, const int y, const int z, const sf::IntRect& rect_textura, const bool& colision, const short& tipo);
		void removerTile(const int x, const int y, const int z);
		void checkColision(Entidades* entidad, const float& DT);

		//Archivos
		void guardarEnArchivo(const std::string nombre_archivo);
		void cargarDesdeArchivo(const std::string nombre_archivo);
		
		// Actualizar - Renderizar
		void actualizar();
		void renderizar(sf::RenderTarget& target, const sf::Vector2i posicionCuadro);
		void renderizacionDiferida(sf::RenderTarget& target);

};

#endif