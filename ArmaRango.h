#ifndef ARMARANGO_H
#define ARMARANGO_H

#include "Armas.h"


class ArmaRango : public Armas
{
	private:

	protected:

	public:
		ArmaRango(int nivel, unsigned valor, std::string ruta_textura);
		virtual ~ArmaRango();

		virtual void actualizar(const sf::Vector2f& posMouseVista, const sf::Vector2f centro) = 0;
		virtual void renderizar(sf::RenderTarget& target, sf::Shader* sombra = nullptr) = 0;
};

#endif
