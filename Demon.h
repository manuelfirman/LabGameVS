#ifndef DEMON_H
#define DEMON_H

#include "Enemigos.h"
#include "IA.h"


class Demon : public Enemigos
{
	private:
		sf::RectangleShape _barraHP;
		IA* _inteligenciaArtificial;

	private:
		void iniciarVariables();
		void iniciarIA();
		void iniciarAnimaciones();
		void iniciarGUI();

	public:
		Demon(float x, float y, sf::Texture& textura, std::map<std::string, sf::SoundBuffer>& sonidos, SpawnerEnemigos& tile_spawner, Entidades& jugador);
		virtual ~Demon();

		void actualizarIA(const float DT);

		void actualizarAnimacion(const float& DT);
		void actualizar(const float& DT, sf::Vector2f& posMouseVista);

		void renderizar(sf::RenderTarget& target, sf::Shader* sombra, const sf::Vector2f posLuz, const bool mostrar_hitbox);
};

#endif