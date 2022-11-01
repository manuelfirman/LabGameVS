#ifndef MANAGERENEMIGOS_H
#define MANAGERENEMIGOS_H

#include "SpawnerEnemigos.h"
#include "Demon.h"
#include "Bat.h"
#include "Slime.h"

enum tipo_enemigo { SLIME = 0, BAT, DEMON };

class ManagerEnemigos
{
	private:
		std::vector<Enemigos*>& _enemigos;
		std::map<std::string, sf::Texture>& _texturas;
		std::map<std::string, sf::SoundBuffer>& _sonidos;
		Entidades& _jugador;

	public:
		ManagerEnemigos(std::vector<Enemigos*>& enemigos, std::map<std::string, sf::Texture>& texturas, std::map<std::string, sf::SoundBuffer>& sonidos, Entidades& jugador);
		~ManagerEnemigos();


		void crearEnemigo(const int tipo_enemigo, const int posX, const int posY, SpawnerEnemigos& tile_spawner);
		void eliminarEnemigo(const int indice);

		void actualizar(const float& DT);
		void renderizar(sf::RenderTarget& target);
};


#endif