#ifndef PROYECTIL_H
#define PROYECTIL_H

class Proyectil
{
	private:
		sf::Sprite _spriteSkill;


		bool _realizando;

		float _dmg;
		float _duracion;
		float _velocidad;
		sf::Vector2f _direccion;
		sf::Vector2f _inicio;
		sf::Clock _duracionClock;


	public:
		Proyectil(sf::Texture& textura, float dmg, float duracion, float velocidad, sf::Vector2f direccion, sf::Vector2f inicio);
		~Proyectil();

		bool getRealizando();
		bool eliminar();
		void actualizar(const float& DT);
		void renderizar(sf::RenderTarget& target);

};

#endif