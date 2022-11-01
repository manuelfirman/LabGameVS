#ifndef ENEMIGOS_H
#define ENEMIGOS_H

#include "Entidades.h"
#include "SpawnerEnemigos.h"
#include "Sonido.h"

class Enemigos : public Entidades
{
	private:
		virtual void iniciarVariables();
		virtual void iniciarAnimaciones();

	protected:
		SpawnerEnemigos& _spawner;
		sf::Clock _timerDmg;
		sf::Int32 _timerDmgMax;
		sf::Clock _timerAtaque;
		sf::Int32 _timerAtaqueMax;
		int _experiencia;
		unsigned _rango;


	public:
		Enemigos(SpawnerEnemigos& tile_spawner);
		virtual ~Enemigos();

		SpawnerEnemigos& getTileSpawner();

		const unsigned& getRango() const;


		void resetTimerAtaque();
		const bool& getAtaqueTerminado() const;

		void resetTimerDmg();
		const bool& getDmgTerminado() const;

		const int& getExperiencia() const;
		virtual void generarAtributos(const int nivel);

		virtual const bool estaVivo() const;
		virtual void perderVida(const int hp);
		virtual const Atributos* getAtributos() const;
		virtual Sonido& getSonido();

		virtual void actualizarAnimacion(const float& DT) = 0;
		virtual void actualizar(const float& DT, sf::Vector2f& posMouseVista) = 0;
		virtual void renderizar(sf::RenderTarget& target, sf::Shader* sombra, const sf::Vector2f posLuz, const bool mostrar_hitbox) = 0;
};

#endif  