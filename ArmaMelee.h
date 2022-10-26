#ifndef ARMAMELEE_H
#define ARMAMELEE_H

#include "Armas.h"


class ArmaMelee : public Armas
{
	private:

	protected:

	public:
		ArmaMelee(int nivel, unsigned valor, std::string ruta_textura);
		virtual ~ArmaMelee();

		virtual void actualizar(const sf::Vector2f& posMouseVista, const sf::Vector2f centro) = 0;
		virtual void renderizar(sf::RenderTarget& target, sf::Shader* sombra = nullptr) = 0;
};

#endif