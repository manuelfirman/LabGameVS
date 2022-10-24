#ifndef ENEMIGOS_H
#define ENEMIGOS_H

#include "Entidades.h"
#include "SpawnerEnemigos.h"

class Enemigos : public Entidades
{
	private:
		//SpawnerEnemigos& _spawner;

	private:
		virtual void iniciarVariables();
		virtual void iniciarAnimaciones();

	public:
		Enemigos();
		virtual ~Enemigos();

		virtual void actualizarAnimacion(const float& DT) = 0;
		virtual void actualizar(const float& DT, sf::Vector2f& posMouseVista) = 0;
		virtual void renderizar(sf::RenderTarget& target, sf::Shader* sombra, const sf::Vector2f posLuz, const bool mostrar_hitbox) = 0;
};

#endif  