#ifndef ARMARANGO_H
#define ARMARANGO_H

#include "Items.h"

class Items;

class ArmaRango : public Items
{
	private:

	protected:
		sf::Texture _texturaArma;
		sf::IntRect _rectTexturaArma;
		sf::Sprite _spriteArma;

		int dmgMin;
		int dmgMax;


	public:
		ArmaRango();
		virtual ~ArmaRango();

		virtual void actualizar(const sf::Vector2f& posMouseVista, const sf::Vector2f centro) = 0;
		virtual void renderizar(sf::RenderTarget& target, sf::Shader* sombra = nullptr) = 0;
};

#endif
