#ifndef JUGADOR_H
#define JUGADOR_H

#include "Entidades.h"
#include "Espada.h"
#include "Orbe.h"
#include "Proyectil.h"


class Jugador : public Entidades
{
private: // Atributos
    bool _atacando;
    Espada* _espada;
    std::vector<Proyectil> _skill;
    sf::Texture _texturaSkill;


private: // Metodos
    void iniciarVariables();
    void iniciarComponentes();


public:
    Jugador(float x, float y, sf::Texture& textura);
    ~Jugador();

    Atributos* getAtributos();
    Armas* getArma() const;

    // Setters
    void ganarHP(const int hp);
    void perderHP(const int hp);

    void ganarExperiencia(const int experiencia);
    void perdeExperiencia(const int experiencia);

    // Actualizar
    //void actualizarAtaque(const float& DT, sf::Vector2f posMouseVista);
    void actualizarAnimacion(const float& DT, sf::Vector2f& posMouseVista);
    void actualizar(const float& DT, sf::Vector2f& posMouseVista);
    
    // Renderizar
    void renderizar(sf::RenderTarget& target, sf::Shader* sombra = NULL, const sf::Vector2f posLuz = sf::Vector2f(), const bool mostrar_hitbox = false);
};

#endif // JUGADOR_H