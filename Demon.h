#ifndef DEMON_H
#define DEMON_H

#include "Enemigos.h"

class Demon : public Enemigos
{
	private:
		sf::RectangleShape _barraHP;
	private:
		void iniciarVariables();
		void iniciarAnimaciones();
		void iniciarGUI();

	public:
		Demon(float x, float y, sf::Texture& textura, SpawnerEnemigos& tile_spawner);
		virtual ~Demon();

		void actualizarAnimacion(const float& DT);
		void actualizar(const float& DT, sf::Vector2f& posMouseVista);

		void renderizar(sf::RenderTarget& target, sf::Shader* sombra, const sf::Vector2f posLuz, const bool mostrar_hitbox);;
};

#endif