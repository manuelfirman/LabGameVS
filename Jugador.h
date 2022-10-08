#ifndef JUGADOR_H
#define JUGADOR_H

#include "Entidades.h"

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

    void actualizarAtaque(const float& DT);
    void actualizarAnimacion(const float& DT);
    void actualizar(const float& DT);
    void renderizar(sf::RenderTarget& target);
};

#endif // JUGADOR_H