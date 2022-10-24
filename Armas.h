#ifndef ARMAS_H
#define ARMAS_H

#include "Items.h"


class Armas : public Items
{
	private:
		void iniciarVariables();
		void iniciarCooldowns();

	protected:
		sf::Texture _texturaArma;
		sf::IntRect _rectTexturaArma;
		sf::Sprite _spriteArma;

		unsigned _rango;
		int _dmgMin;
		int _dmgMax;

		float cooldown;
		float cooldownMax;
		float cooldownIt;

		
	public:
		Armas(unsigned valor, std::string ruta_textura);
		~Armas();

		const int& getDmgMin() const;
		const int& getDmgMax() const;
		const unsigned& getRango() const;

		virtual void actualizar(const sf::Vector2f& posMouseVista, const sf::Vector2f centro) = 0;
		virtual void renderizar(sf::RenderTarget& target, sf::Shader* sombra = nullptr) = 0;
};

#endif
