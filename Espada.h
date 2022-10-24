#ifndef ESPADA_H
#define ESPADA_H

#include "ArmaMelee.h"
#include "Animacion.h"


class ArmaMelee;
class Animacion;

class Espada : public ArmaMelee
{
	private:
		


	public:
		Espada(unsigned valor, std::string ruta_textura);
		~Espada();

		void actualizar(const sf::Vector2f& posMouseVista, const sf::Vector2f centro);
		void renderizar(sf::RenderTarget& target, sf::Shader* sombra = nullptr);
};

#endif