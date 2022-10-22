#ifndef ENEMIGOS_H
#define ENEMIGOS_H

#include "Entidades.h"
#include "SpawnerEnemigos.h"

class Enemigos : public Entidades
{
	private:
		//SpawnerEnemigos& _spawner;

	private:
		void iniciarVariables();
		void iniciarAnimaciones();

	public:
		Enemigos(float x, float y, sf::Texture& textura);
		virtual ~Enemigos();

		void actualizarAnimacion(const float& DT);
		void actualizar(const float& DT, sf::Vector2f& posMouseVista);
		void renderizar(sf::RenderTarget& target, sf::Shader* sombra, const sf::Vector2f posLuz, const bool mostrar_hitbox);
};

#endif