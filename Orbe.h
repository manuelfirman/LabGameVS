#ifndef ORBE_H
#define ORBE_H

#include "ArmaRango.h"


class Orbe : public ArmaRango
{
	private:

	public:
		Orbe(int nivel, unsigned valor, std::string ruta_textura);
		~Orbe();

		void actualizar(const sf::Vector2f& posMouseVista, const sf::Vector2f centro);
		void renderizar(sf::RenderTarget& target, sf::Shader* sombra = nullptr);
};

#endif