#ifndef JUGADOR_H
#define JUGADOR_H

#include "Entidades.h"
#include "Espada.h"

class Entidades;
class Espada;


class Jugador : public Entidades
{
private: // Atributos
    bool _atacando;
    Espada _espada;



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

    // Actualizar
    void actualizarAtaque(const float& DT);
    void actualizarAnimacion(const float& DT, sf::Vector2f& posMouseVista);
    void actualizar(const float& DT, sf::Vector2f& posMouseVista);
    
    // Renderizar
    void renderizar(sf::RenderTarget& target, sf::Shader* sombra = NULL, const bool mostrar_hitbox = false);
};

#endif // JUGADOR_H