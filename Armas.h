#ifndef ARMAS_H
#define ARMAS_H

#include "Items.h"


class Armas : public Items
{
	private:
		void iniciarVariables();

	protected:
		sf::Texture _texturaArma;
		sf::IntRect _rectTexturaArma;
		sf::Sprite _spriteArma;

		unsigned _rango;
		int _dmgMin;
		int _dmgMax;

		sf::Clock _timerAtaque;
		sf::Int32 _timerAtaqueMax; // de -2millones a +2millones

		
		
	public:
		Armas(int nivel, unsigned valor, std::string ruta_textura);
		~Armas();
		// TODO: Hacer otro constructor con: (nivel, valor, daño minimo, daño maximo, rango, ruta textura) para no hardcodear cada arma
		// TODO: Metodo para generar armas (dentro de ArmaMelee y ArmaRango) a partir del nivel del personaje


		const int& getDmgMin() const;
		const int& getDmgMax() const;
		const int getDMG() const;
		const unsigned& getRango() const;
		const bool getTimerAtaque();

		virtual void actualizar(const sf::Vector2f& posMouseVista, const sf::Vector2f centro) = 0;
		virtual void renderizar(sf::RenderTarget& target, sf::Shader* sombra = nullptr) = 0;
};

#endif
