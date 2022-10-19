#ifndef ENTIDADES_H
#define ENTIDADES_H

#include "Hitbox.h"
#include "Movimiento.h"
#include "Animacion.h"
#include "Atributos.h"

class Hitbox;
class Movimiento;
class Animacion;
class Atributos;


class Entidades
{
private: // Metodos
    void iniciarVariables();

protected: // Atributos
    sf::Sprite _sprite;

    Movimiento* _movimiento;
    Animacion* _animacion;
    Hitbox* _hitbox;
    Atributos* _atributos;


public:
    Entidades();
    virtual ~Entidades();
    // Funciones de componentes
    void setTextura(sf::Texture& textura);

    /// Componentes
    void crearHitbox(sf::Sprite& sprite, float x, float y, float ancho, float alto);
    void crearComponenteMovimiento(float velocidadMaxima, float aceleracion, float desaceleracion);
    void crearComponenteAnimacion(sf::Texture& textura);
    void crearComponenteAtributos(const int nivel);

    // Getters
    virtual const sf::Vector2f& getPosicionSprite() const;
    virtual const sf::Vector2f getCentro() const;
    virtual const sf::Vector2i getCuadroActual(const int tamanioCuadro) const;
    virtual const sf::FloatRect getLimites() const;
    virtual const sf::FloatRect getLimitesPosSiguiente(const float& DT) const;

    // Setters
    virtual void setPosicion(const float x, const float y);

    /// Funciones (Overriders)
    virtual void detenerXY();
    virtual void detenerX();
    virtual void detenerY();
    virtual void mover(const float x, const float y, const float& DT);

    virtual void actualizar(const float& DT, sf::Vector2f& posMouseVista) = 0;
    virtual void renderizar(sf::RenderTarget& target, sf::Shader* sombra, const bool mostrar_hitbox = false) = 0;
};

#endif // ENTIDADES_H