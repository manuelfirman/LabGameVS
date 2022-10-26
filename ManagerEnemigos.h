#ifndef MANAGERENEMIGOS_H
#define MANAGERENEMIGOS_H

#include "SpawnerEnemigos.h"
#include "Demon.h"

enum tipo_enemigo { DEMON = 0, GOBLIN };

class ManagerEnemigos
{
	private:
		std::vector<Enemigos*>& _enemigos;
		std::map<std::string, sf::Texture>& _texturas;
		
	public:
		ManagerEnemigos(std::vector<Enemigos*>& enemigos, std::map<std::string, sf::Texture>& texturas);
		~ManagerEnemigos();


		void crearEnemigo(const int tipo_enemigo, const int posX, const int posY, SpawnerEnemigos& tile_spawner);
		void eliminarEnemigo(const int indice);

		void actualizar(const float& DT);
		void renderizar(sf::RenderTarget& target);
};


#endif