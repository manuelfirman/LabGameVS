#ifndef ESPADA_H
#define ESPADA_H

#include "ArmaMelee.h"
#include "Animacion.h"


class Espada : public ArmaMelee
{
	private:

	public:
		Espada(int nivel, unsigned valor, std::string ruta_textura);
		~Espada();

		void animacionAtaque(const sf::Vector2f& posMouseVista, const sf::Vector2f centro, const bool twistear);
		void actualizar(const sf::Vector2f& posMouseVista, const sf::Vector2f centro);
		void renderizar(sf::RenderTarget& target, sf::Shader* sombra = nullptr);
};

#endif