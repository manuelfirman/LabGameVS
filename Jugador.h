#ifndef JUGADOR_H
#define JUGADOR_H

#include "Entidades.h"

class Entidades;

class Jugador : public Entidades
{
private: // Atributos
    bool _atacando;


private: // Metodos
    void iniciarVariables();
    void iniciarComponentes();

public:
    Jugador(float x, float y, sf::Texture& textura);
    ~Jugador();

    Atributos* getAtributos();



    // Setters
    void ganarHP(const int hp);
    void perderHP(const int hp);

    void ganarExperiencia(const int experiencia);
    void perdeExperiencia(const int experiencia);


    void actualizarAtaque(const float& DT);
    void actualizarAnimacion(const float& DT);
    void actualizar(const float& DT);
    void renderizar(sf::RenderTarget& target, const bool mostrar_hitbox = false);
};

#endif // JUGADOR_H