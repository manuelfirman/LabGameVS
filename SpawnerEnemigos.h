#ifndef SPAWNERENEMIGOS_H
#define SPAWNERENEMIGOS_H

#include "Tile.h"

class SpawnerEnemigos : public Tile
{
	private:
		bool _spawneado;
		sf::RectangleShape testShape;
		sf::Vector2i _posicionCuadro;
		int _tipoEnemigo;
		int _cantidadEnemigos;
		float _distanciaMax;

		sf::Clock _timerSpawn;
		sf::Int32 _tiempoSpawn;
		int _contadorEnemigos;


	public:
		SpawnerEnemigos(int cuadro_x, int cuadro_y, float tamanioCuadroF, sf::Texture& textura, const sf::IntRect& rect_textura,
			int tipo_enemigo, int cantidad_enemigos, sf::Int32 tiempo_spawn, float distancia_max);
		virtual ~SpawnerEnemigos();

		void resetTimer();
		void setSpawn(const bool spawneado);
		const bool& getSpawn();
		const bool puedeSpawnear();
		const int& getContadorEnemigos() const;
		const int& getCantidadMaxEnemigos() const;
		virtual const std::string getTileString() const;
		const int& getTipoEnemigo();
		
		void contEnemigosMasMas();
		void contEnemigosMenosMenos();

		void actualizar();
		void renderizar(sf::RenderTarget& target, const sf::Vector2f posicionJugador, sf::Shader* sombra);

};

#endif // !SPAWNERENEMIGOS_H
