#ifndef SPAWNERENEMIGOS_H
#define SPAWNERENEMIGOS_H


class SpawnerEnemigos
{
	private:
		sf::Vector2i _posicionCuadro;
		int _tipo;
		int _cantidad;
		int _tiempoSpawn;
		float _distanciaMax;


	public:
		SpawnerEnemigos(sf::Vector2i posicion, int tipo, int cantidad, int tiempo_spawn, float distancia_max);
		virtual ~SpawnerEnemigos();

		void spawn();
		void limpiar();

		void actualizar(const float& DT);
		void renderizar(sf::RenderTarget& target);

};

#endif // !SPAWNERENEMIGOS_H
