#ifndef ARMAMELEE_H
#define ARMAMELEE_H

#include "Items.h"
#include "Movimiento.h"

class Item;
class Movimiento;

class ArmaMelee : public Items
{
	private:

	protected:
		sf::Texture _texturaArma;
		sf::IntRect _rectTexturaArma;
		sf::Sprite _spriteArma;

		int dmgMin;
		int dmgMax;


	public:
		ArmaMelee();
		virtual ~ArmaMelee();

		virtual void actualizar(const sf::Vector2f& posMouseVista, const sf::Vector2f centro) = 0;
		virtual void renderizar(sf::RenderTarget& target, sf::Shader* sombra = nullptr) = 0;
};

#endif