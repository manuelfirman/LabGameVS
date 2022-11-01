#ifndef BAT_H
#define BAT_H

#include "Enemigos.h"
#include "IA.h"


class Bat : public Enemigos
{
private:
	sf::RectangleShape _barraHP;
	IA* _inteligenciaArtificial;

private:
	void iniciarVariables();
	void iniciarIA();
	void iniciarAnimaciones();
	void iniciarGUI();

public:
	Bat(float x, float y, sf::Texture& textura, std::map<std::string, sf::SoundBuffer>& sonidos, SpawnerEnemigos& tile_spawner, Entidades& jugador);
	virtual ~Bat();

	void actualizarIA(const float DT);

	void actualizarAnimacion(const float& DT);
	void actualizar(const float& DT, sf::Vector2f& posMouseVista);

	void renderizar(sf::RenderTarget& target, sf::Shader* sombra, const sf::Vector2f posLuz, const bool mostrar_hitbox);
};

#endif