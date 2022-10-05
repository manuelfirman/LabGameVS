#ifndef ENTIDADES_H
#define ENTIDADES_H

#include "Hitbox.h"
#include "Movimiento.h"
#include "Animacion.h"

class Entidades
{
private: // Metodos
    void iniciarVariables();



protected: // Atributos
    sf::Sprite _sprite;

    Movimiento* _movimiento;
    Animacion* _animacion;
    Hitbox* _hitbox;



public:
    Entidades();
    virtual ~Entidades();
    // Funciones de componentes
    void setTextura(sf::Texture& textura);

    /// Componentes
    void crearHitbox(sf::Sprite& sprite, float x, float y, float ancho, float alto);
    void crearComponenteMovimiento(float velocidadMaxima, float aceleracion, float desaceleracion);
    void crearComponenteAnimacion(sf::Texture& textura);

    /// Overriders
    virtual void setPosicion(const float x, const float y);
    virtual void mover(const float x, const float y, const float& DT);

    virtual void actualizar(const float& DT);
    virtual void renderizar(sf::RenderTarget& target);
};

#endif // ENTIDADES_H