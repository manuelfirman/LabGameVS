#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include "TileNormal.h"

#include "ManagerEnemigos.h"
#include "SpawnerEnemigos.h"
#include "Entidades.h"
#include "Demon.h"


class TileMap
{
	private:
		float _tamanioCuadroF;
		sf::Vector2i _tamanioMaxCuadros;
		sf::Vector2f _tamanioMaxMundo;
		int _tamanioCuadroI;
		int _Capas;
		std::stack<Tile*> _pilaRenderDiferida;

		// (x , y , capas , pila de capas)
		std::vector <std::vector < std::vector < std::vector <Tile*> > > > _mapa; // si, son 4 xD
		sf::RectangleShape _cajaColisiones;
		
		std::string _archivoTextura;
		sf::Texture _texturaTile;

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
		TileMap(const std::string archivo_textura);
		virtual ~TileMap();

		// Getters
		const sf::Texture* getTexturaTile() const;
		const int getTilesPorCuadro(const int x,const int y,const int capa) const;
		const sf::Vector2f& getTamanioMax() const;
		const sf::Vector2i& getTamanioMaxCuadros() const;
		const bool tileVacio(const int x, const int y, const int z) const;

		// Metodos
		void agregarTile(const int x, const int y, const int z, const sf::IntRect& rect_textura, const bool& colision, const short& tipo);
		void agregarTile(const int x, const int y, const int z, const sf::IntRect& rect_textura, const int tipo_enemigo, const int cantidad_enemigos, const int tiempo_spawn, const int distancia_max);
		void removerTile(const int x, const int y, const int z, const int tipo = -1);
		void checkColision(Entidades* entidad, const float& DT);
		const bool verificarTipoTile(const int x, const int y, const int z, const int tipo) const;

		//Archivos
		void guardarEnArchivo(const std::string nombre_archivo);
		void cargarDesdeArchivo(const std::string nombre_archivo);

		// Actualizar - Renderizar
		void actualizarLimitesMapa(Entidades* entidad, const float& DT);
		void actualizarTiles(Entidades* entidad, const float& DT, ManagerEnemigos& manager_enemigos);

		void renderizar(sf::RenderTarget& target, const sf::Vector2i& posicionCuadro, sf::Vector2f posicionJugador = sf::Vector2f(), sf::Shader* sombra = NULL, const bool mostrar_hitbox = true);
		void renderizacionDiferida(sf::RenderTarget& target, const sf::Vector2f posicionJugador = sf::Vector2f(), sf::Shader* sombra = NULL);

};

#endif